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
    std::cout << "distance: "<<distance<<std::endl;
    std::cout << "zHat: "<<zHat <<std::endl;
    double delta=(distance-zHat);
    std::cout <<"Delta: "<<delta<<std::endl;
    RowVector3d H=jacobianObservationModel(robotPos);
    std::cout <<"H: "<<H<<std::endl;
    double Q=H*covariance*(H.transpose())+pingerVariance;
    std::cout << "Q: "<<Q<<std::endl;
    Vector3d K=(1/Q)*covariance*(H.transpose());
    std::cout <<"Kalman Gain: "<<K.transpose()<<std::endl;
    //mean=mean+K*delta;
    std::cout << "K*delta: " <<K*delta<<std::endl;
    covariance=(Matrix<double,3,3>::Identity()-K*H)*covariance;
    weight=(1/sqrt(2*M_PI*abs(Q)))*exp((-0.5/Q)*pow(delta,2));
    std::cout << "weight returned after KF update: "<<weight<<std::endl;
    return weight;
}

double KalmanFilter::observation(Vector3d robotPosition)
{
    std::cout << "mean: " <<mean<<std::endl;
    std::cout << "robotPosition: "<<robotPosition<<std::endl;
    Vector3d v=mean-robotPosition;
    std::cout << "v: " <<v<<std::endl;
    return (mean-robotPosition).norm();
}


RowVector3d KalmanFilter::jacobianObservationModel(Vector3d robotPosition)
{
    RowVector3d res;
    Vector3d tmp=(mean-robotPosition);
    std::cout<<"Tmp: "<<tmp.transpose()<<std::endl;
    res=(tmp/tmp.squaredNorm()).transpose(); // TODO test if it works
    std::cout<<"Res: "<<res<<std::endl;
    return res;
}
