#include "kalmanfilter.h"
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
