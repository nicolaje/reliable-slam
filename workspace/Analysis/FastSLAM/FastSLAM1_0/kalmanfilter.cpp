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
    std::cout <<"Delta: "<<delta<<std::endl;
    RowVector3d H=jacobianObservationModel(robotPos);
    double Q=H*covariance*(H.transpose())+pingerVariance;
    std::cout << "Q: "<<Q<<std::endl;
    Vector3d K=(1/Q)*covariance*(H.transpose());
    std::cout <<"Kalman Gain: "<<K.transpose()<<std::endl;
    mean=mean+K*delta;
    covariance=(Matrix<double,3,3>::Identity()-K*H)*covariance;
    weight=(1/sqrt(2*M_PI*abs(Q)))*exp((-0.5/Q)*pow(delta,2));
    std::cout << "weight returned after KF update: "<<weight<<std::endl;
    return weight;
}

double KalmanFilter::observation(Vector3d robotPosition)
{
    return (mean-robotPosition).squaredNorm();
}


RowVector3d KalmanFilter::jacobianObservationModel(Vector3d robotPosition)
{
    RowVector3d res;
    Vector3d tmp=(mean-robotPosition);
    res=(tmp/tmp.squaredNorm()).transpose(); // TODO test if it works
    return res;
}
