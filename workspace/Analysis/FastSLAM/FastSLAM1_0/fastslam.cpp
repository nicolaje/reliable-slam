#include "fastslam.h"
#include "resampling.h"
#include <iostream>
#define SEED 1

using namespace Eigen;

std::default_random_engine FastSLAM::generator=std::default_random_engine(SEED);

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
        Particle p(robotPosition, robotOrientation, robotLinearMotion, robotAngularMotion, landmarksPosEstimates, landmarksCovEstimates,pingerVariance);
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
    for(int l=0;l<landmarksMeasurements.size();l++){
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
    std::normal_distribution<double> distribution(0,1);

}


void FastSLAM::updateRobotOrientation(Vector3d orientation)
{
}


void FastSLAM::updateRobotPosition(Vector3d position)
{
}
