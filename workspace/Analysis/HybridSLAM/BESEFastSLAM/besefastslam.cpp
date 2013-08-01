#include "besefastslam.h"

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

}

void BESEFastSLAM::update(ibex::IntervalVector data)
{

}
