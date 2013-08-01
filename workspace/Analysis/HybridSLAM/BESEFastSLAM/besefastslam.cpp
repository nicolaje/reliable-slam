#include "besefastslam.h"
#include <ibex/ibex.h>
#include <eigen3/Eigen/Eigen>
#include <../../General/Utils/utils.h>

using namespace Eigen;
using namespace ibex;

BESEFastSLAM::BESEFastSLAM(int particleNb, ibex::IntervalVector initState, int nbRobots, int nbLandmarks)
{
    this->beseEstimator=new BESE(initState,nbRobots,nbLandmarks);
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

void BESEFastSLAM::predict(ibex::Interval dt)
{
    this->beseEstimator->predict(dt);
    for(int i=0;i<particleNb;i++){
        particles[i].predict(dt.mid());
    }
}

void BESEFastSLAM::update(ibex::IntervalVector data)
{

}


void BESEFastSLAM::reSample()
{
    IntervalVector robotPosition=beseEstimator->getPosition();
    IntervalVector robotOrientation=beseEstimator->getOrientation();

    IntervalVector map=beseEstimator->getMap();


}


bool BESEFastSLAM::isConsistent(IntervalVector iVector, VectorXd eVector)
{
    return iVector.contains(Utils::eigenVectorToIntervalVector(eVector));
}
