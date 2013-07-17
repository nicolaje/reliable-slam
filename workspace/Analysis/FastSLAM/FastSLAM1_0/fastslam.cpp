#include "fastslam.h"
using namespace Eigen;
FastSLAM::FastSLAM(Matrix3d positionCovariance, Matrix3d orientationCovariance, Matrix3d linearMotionCovariance, Matrix3d angularMotionCovariance, double pingerVariance, uint RESAMPLE_METHOD, uint RESAMPLE_STRATEGY)
{
    this->positionCovariance=positionCovariance;
    this->orientationCovariance=orientationCovariance;
    this->linearMotionCovariance=linearMotionCovariance;
    this->angularMotionCovariance=angularMotionCovariance;
    this->pingerVariance=pingerVariance;
    this->resampling_method=RESAMPLE_METHOD;
    this->resampling_strategy=RESAMPLE_STRATEGY;
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
        }
    }
}

void FastSLAM::updateRobotMotion(Vector3d linearMotion, Vector3d angularMotion)
{
}


void FastSLAM::updateRobotOrientation(Vector3d orientation)
{
}


void FastSLAM::updateRobotPosition(Vector3d position)
{
}
