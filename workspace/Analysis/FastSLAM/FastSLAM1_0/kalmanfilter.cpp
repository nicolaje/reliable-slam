#include "kalmanfilter.h"
#include <iostream>
using namespace Eigen;
KalmanFilter::KalmanFilter(Vector3d mean, Matrix3d covariance, double pingerVariance)
{
    this->mean=mean;
    this->covariance=covariance;
    this->pingerVariance=pingerVariance;
}

void KalmanFilter::predict(double dt)
{
    // Landmarks do not move in our situation, do nothing =)
}
double KalmanFilter::update(double distance, Vector3d robotPos)
{
    double weight=0;
    double zHat=observation(robotPos);
    double delta=(distance-zHat);
    RowVector3d H=jacobianObservationModel(robotPos);
    double Q=H*covariance*(H.transpose())+pingerVariance;
    Vector3d K=(1/Q)*covariance*(H.transpose());
    mean=mean+K*delta;
    covariance=(Matrix<double,3,3>::Identity()-K*H)*covariance;
    weight=(1/sqrt(2*M_PI*abs(Q)))*exp((-0.5/Q)*pow(delta,2));
    return weight;
}

double KalmanFilter::observation(Vector3d robotPosition)
{
    Vector3d v=mean-robotPosition;
    return (mean-robotPosition).norm();
}


RowVector3d KalmanFilter::jacobianObservationModel(Vector3d robotPosition)
{
    RowVector3d res;
    Vector3d tmp=(mean-robotPosition);
    res=(tmp/tmp.norm()).transpose();
    return res;
}
