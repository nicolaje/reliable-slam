#include "fastslam.h"
#include "resampling.h"
#include <iostream>
#define SEED 1
#define SIGMA_FACTOR 5

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
        // TODO: find a way to draw landmark positions from a multivariate normal distribution (http://stackoverflow.com/questions/6142576/sample-from-multivariate-normal-gaussian-distribution-in-c could do? )
        // But for now, all the particles are init the same,
        // next step is drawing from uniform distribution, and doing it wrong because assuming the cov matrices are diagonals!
        for(uint j=0;j<landmarksPosEstimates.size();j++){
            Vector3d pos=landmarksPosEstimates[j];
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
    for(uint l=0;l<landmarksMeasurements.size();l++){
        for(int i=0;i<particleNb;i++){
            particles[i].updateKF(landmarksMeasurements[l],l);
            if(resampling_strategy==RESAMPLE_EVERYTIME){
                normalize();
                reSample();
            }
        }
        normalize();
        if(resampling_strategy==RESAMPLE_EACH)
            reSample();
    }
    if(resampling_strategy==RESAMPLE_ALL)
        reSample();
}

void FastSLAM::reSample()
{
    switch(resampling_method){
    case ROULETTE:
        ReSampling::resamplingRoulette(particles);
        break;
    case ROULETTE_1ST_QUARTIL:
        ReSampling::resamplingPercentil(particles,25);
        break;
    case ROULETTE_2ST_QUARTIL:
        ReSampling::resamplingPercentil(particles,50);
        break;
    case ROULETTE_3ST_QUARTIL:
        ReSampling::resamplingPercentil(particles,75);
        break;
    case ROULETTE_PERCENTIL:
        ReSampling::resamplingPercentil(particles,percentil);
        break;
    default:
        ReSampling::resamplingRoulette(particles);
    }
}

void FastSLAM::setPercentilResampling(int percentil)
{
    this->percentil=percentil;
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
