#include "fastslam.h"
#include "resampling.h"
#include <iostream>
#define SEED 1
#define SIGMA_FACTOR 30

using namespace Eigen;

std::default_random_engine FastSLAM::generator=std::default_random_engine(SEED);

std::vector<Vector3d> FastSLAM::drawSamples(int nb, Vector3d mean, Matrix3d covariance)
{
    std::vector<Vector3d> samples;
    SelfAdjointEigenSolver<MatrixXd> eigenSolver(covariance);
    std::normal_distribution<double> norm(0,1);

    Matrix3d rot=eigenSolver.eigenvectors();
    Vector3d scl=eigenSolver.eigenvalues();
    for(int i=0; i<nb; i++){
        Vector3d v(scl(0)*norm(generator),scl(1)*norm(generator),scl(2)*norm(generator)); // scale
        v=rot*v; // rotate
        samples.push_back(mean+v);
    }
    return samples;
}

std::vector<Vector3d> FastSLAM::drawSamples(int nb, ibex::IntervalVector box)
{
    std::vector<Vector3d> samples;
    std::uniform_real_distribution<> uniform(0,1);
    for(int i=0;i<nb;i++){
        Vector3d v;
        for(int j=0;j<3;j++)
            v[j]=uniform(generator)*box[j].diam()+box[j].lb();
        samples.push_back(v);
    }
    return samples;
}

FastSLAM::FastSLAM(Matrix3d positionCovariance, Matrix3d orientationCovariance, Matrix3d linearMotionCovariance, Matrix3d angularMotionCovariance, double pingerVariance, uint RESAMPLE_METHOD, uint RESAMPLE_STRATEGY, int percentil)
{
    this->positionCovariance=positionCovariance;
    this->orientationCovariance=orientationCovariance;
    this->linearMotionCovariance=linearMotionCovariance;
    this->angularMotionCovariance=angularMotionCovariance;
    this->pingerVariance=pingerVariance;
    this->resampling_method=RESAMPLE_METHOD;
    this->resampling_strategy=RESAMPLE_STRATEGY;
    this->percentil=percentil;
}

void FastSLAM::initParticles(int particleNb, Vector3d robotPosition, Vector3d robotOrientation, Vector3d robotLinearMotion, Vector3d robotAngularMotion, std::vector<Vector3d> landmarksPosEstimates, std::vector<Matrix3d> landmarksCovEstimates)
{
    this->particleNb=particleNb;
    for(int i=0; i<particleNb; i++){
        Particle p(robotPosition, robotOrientation, robotLinearMotion, robotAngularMotion);
        std::vector<KalmanFilter> initMap;
        for(uint j=0;j<landmarksPosEstimates.size();j++){
            Vector3d pos=FastSLAM::drawSamples(1,landmarksPosEstimates[j],landmarksCovEstimates[j])[0];
            Matrix3d posCov=landmarksCovEstimates[j];
            KalmanFilter kf(pos, posCov, this->pingerVariance);
            initMap.push_back(kf);
        }
        p.setInitMap(initMap);
        particles.push_back(p);
    }
}

void FastSLAM::predict(double dt)
{
    for(int i=0;i<particleNb;i++){
        particles[i].predict(dt);
    }
}

void FastSLAM::updateMap(std::vector<double> landmarksMeasurements)
{
    if(resampling_method!=RESAMPLE_ALL_AT_ONCE){
        for(uint l=0;l<landmarksMeasurements.size();l++){
            for(int i=0;i<particleNb;i++){
                particles[i].updateKF(landmarksMeasurements[l],l);
                Vector3d zeroMean;
                zeroMean << 0,0,0;
                particles[i].addMapError(FastSLAM::drawSamples(1,zeroMean,this->errorCovariance)[0],l);
                if(resampling_method==RESAMPLE_EVERYTIME){
                    std::cout<<"Resampling everytime"<<std::endl;
                    normalize();
                    particles=reSample();
                }
            }
            normalize();
            if(resampling_method==RESAMPLE_EACH){
                std::cout<<"Resampling after each landmark"<<std::endl;
                particles=reSample();
            }
        }
        if(resampling_method==RESAMPLE_ALL){
            std::cout<<"Resampling after every landmark has been incorporated in every particle"<<std::endl;
            particles=reSample();
        }
    }else{
        for(int p=0;p<particleNb;p++){
            particles[p].updateAllKFs(landmarksMeasurements);
        }
        normalize();
        particles=reSample();
    }
}

    std::vector<Particle> FastSLAM::reSample()
    {
        switch(resampling_strategy){
        case ROULETTE:
            return ReSampling::resamplingRoulette(particles);
            break;
        case ROULETTE_1ST_QUARTIL:
            return ReSampling::resamplingPercentil(particles,25);
            break;
        case ROULETTE_2ST_QUARTIL:
            return ReSampling::resamplingPercentil(particles,50);
            break;
        case ROULETTE_3ST_QUARTIL:
            return ReSampling::resamplingPercentil(particles,75);
            break;
        case ROULETTE_PERCENTIL:
            return ReSampling::resamplingPercentil(particles,percentil);
            break;
        default:
            return ReSampling::resamplingRoulette(particles);
        }
    }

    void FastSLAM::setPercentilResampling(int percentil)
    {
        this->percentil=percentil;
    }

    void FastSLAM::setErrorCovariance(Matrix3d errorCovariance)
    {
        this->errorCovariance=errorCovariance;
    }

    Particle FastSLAM::getBestParticle()
    {
        double w=0;
        int idx=0;
        for(int i=0;i<particleNb;i++){
            if(particles[i].getWeight()>w){
                w=particles[i].getWeight();
                idx=i;
            }
        }
        return particles[idx];
    }

    void FastSLAM::normalize()
    {
        double sum=0;
        for(int i=0;i<particleNb;i++){
            sum+=particles[i].getWeight();
        }
        for(int i=0;i<particleNb;i++){
            particles[i].normalizeWeight(sum);
        }
    }

    void FastSLAM::updateRobotMotion(Vector3d linearMotion, Vector3d angularMotion)
    {
        std::vector<Vector3d> linearMotions=FastSLAM::drawSamples(particleNb,linearMotion,SIGMA_FACTOR*this->linearMotionCovariance);
        std::vector<Vector3d> angularMotions=FastSLAM::drawSamples(particleNb,angularMotion,SIGMA_FACTOR*this->angularMotionCovariance);
        for(int i=0;i<particleNb;i++){
            particles[i].updateRobotLinearMotion(linearMotions[i]);
            particles[i].updateRobotOrientationMotion(angularMotions[i]);
        }
    }

    void FastSLAM::updateRobotOrientation(Vector3d orientation)
    {
        std::vector<Vector3d> orientations=FastSLAM::drawSamples(particleNb,orientation,orientationCovariance);
        for(int i=0;i<particleNb;i++){
            particles[i].updateRobotOrientation(orientations[i]);
        }
    }

    void FastSLAM::updateRobotPosition(Vector3d position)
    {
        std::vector<Vector3d> positions=FastSLAM::drawSamples(particleNb,position,positionCovariance);
        for(int i=0;i<particleNb;i++){
            particles[i].updateRobotPosition(positions[i]);
        }
    }

    void FastSLAM::updateRobotDepth(double depth)
    {
        Vector3d v3d;
        v3d<<0,0,depth;
        std::vector<Vector3d> positions=FastSLAM::drawSamples(particleNb,v3d,positionCovariance);
        for(int i=0;i<particleNb;i++)
            particles[i].updateRobotDepth(positions[i][2]);
    }
