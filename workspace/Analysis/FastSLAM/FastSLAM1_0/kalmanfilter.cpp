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

Vector3d KalmanFilter::getMean()
{
    return mean;
}
double KalmanFilter::update(double distance, Vector3d robotPos)
{
    double zHat=observation(robotPos);
    double delta=(distance-zHat);
    RowVector3d H=jacobianObservationModel(robotPos);
    double Q=H*covariance*(H.transpose())+pingerVariance;
    Vector3d K=(1/Q)*covariance*(H.transpose());
    std::cout << "distance: " << distance << std::endl;
    std::cout << "zHat: " << zHat << std::endl;
//    std::cout << "delta: " << delta << std::endl;
//    std::cout << "K*delta: " <<K*delta << std::endl;
//    std::cout << "Mean: "<<mean<<std::endl;
//    std::cout <<"Mean+K*delta: "<<mean+K*delta<<std::endl;
    mean=mean+K*delta;
    covariance=(Matrix<double,3,3>::Identity()-K*H)*covariance;
    //    std::cout << "H: " << H << std::endl;
    //    std::cout << "Q: " << Q << std::endl;
    //    std::cout << "K: " << K << std::endl;
    //    std::cout << "Covariance: " << covariance << std::endl;
    //    std::cout << "fabs(Q): " << fabs(Q) << std::endl;
    //    std::cout << "weight: " << weight << std::endl;
    return (1/sqrt(2*M_PI*Q))*exp((-0.5/Q)*pow(delta,2));

}

double KalmanFilter::observation(Vector3d robotPosition)
{
    return (mean-robotPosition).norm();
}


RowVector3d KalmanFilter::jacobianObservationModel(Vector3d robotPosition)
{
    Vector3d tmp=(mean-robotPosition);
    return (tmp/tmp.norm()).transpose();
}
