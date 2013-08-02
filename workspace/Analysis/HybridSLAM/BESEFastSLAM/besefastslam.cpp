#include "besefastslam.h"
#include <ibex/ibex.h>
#include <eigen3/Eigen/Eigen>
#include <../../General/Utils/utils.h>

using namespace Eigen;
using namespace ibex;

BESEFastSLAM::BESEFastSLAM(int particleNb, ibex::IntervalVector initState, int nbRobots, int nbLandmarks)
{
    this->beseEstimator=new BESE(initState,nbRobots,nbLandmarks);
    this->particleNb=particleNb;
}

void BESEFastSLAM::setPositionCovariance(Eigen::Matrix3d positionCovariance)
{
    this->positionCovariance=positionCovariance;
}

void BESEFastSLAM::setOrientationCovariance(Eigen::Matrix3d orientationCovariance)
{
    this->orientationCovariance=orientationCovariance;
}

void BESEFastSLAM::setLinearMotionCovariance(Eigen::Matrix3d linearMotionCovariance)
{
    this->linearMotionCovariance=linearMotionCovariance;
}

void BESEFastSLAM::setAngularMotionCovariance(Eigen::Matrix3d angularMotionCovariance)
{
    this->angularMotionCovariance=angularMotionCovariance;
}

void BESEFastSLAM::setPingerCovariance(double pingerVariance)
{
    this->pingerVariance=pingerVariance;
}

void BESEFastSLAM::initParticles()
{
    Vector3d robotPosition,robotOrientation,robotLinearMotion,robotAngularMotion;

        robotPosition=Utils::intervalVectorToEigenVector(this->beseEstimator->getPosition());
        robotOrientation=Utils::intervalVectorToEigenVector(this->beseEstimator->getOrientation());
        robotLinearMotion=Utils::intervalVectorToEigenVector(this->beseEstimator->getLinearMotion());
        robotAngularMotion=Utils::intervalVectorToEigenVector(this->beseEstimator->getAngularMotion());


    for(int i=0; i<particleNb; i++){
        Particle p(robotPosition, robotOrientation, robotLinearMotion, robotAngularMotion);
        std::vector<KalmanFilter> initMap;
        for(uint j=0;j<beseEstimator->getLandmarkNB();j++){
            Vector3d pos=FastSLAM::drawSamples(1,beseEstimator->getLandmark(j))[0];
            Matrix3d posCov=Utils::boxToCovarianceMatrix(beseEstimator->getLandmark(j),3);
//            KalmanFilter kf(pos, posCov, this->pingerVariance);
//            initMap.push_back(kf);
        }
        p.setInitMap(initMap);
        particles.push_back(p);
    }
}

void BESEFastSLAM::predict(ibex::Interval dt)
{
    this->beseEstimator->predict(dt);
    for(int i=0;i<particleNb;i++){
        particles[i].predict(dt.mid());
    }
}

void BESEFastSLAM::update(ibex::IntervalVector data)
{
    this->beseEstimator->update(data);
}


void BESEFastSLAM::reSample()
{
    IntervalVector robotPosition=beseEstimator->getPosition();
    IntervalVector robotOrientation=beseEstimator->getOrientation();

    IntervalVector map=beseEstimator->getMap();


}


bool BESEFastSLAM::isConsistent(IntervalVector iVector, VectorXd eVector)
{
    return iVector.is_superset(Utils::eigenVectorToIntervalVector(eVector));
}
