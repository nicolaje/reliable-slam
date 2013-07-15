#ifndef KALMANFILTER_H
#define KALMANFILTER_H
#include <eigen3/Eigen/Eigen>

/**
 * @brief The KalmanFilter class is a Kalman Filter to estimate the 3D position of
 * one single landmark.
 */
class KalmanFilter
{
public:
    KalmanFilter(Eigen::Vector3d mean, Eigen::Matrix3d covariance, double pingerVariance);
    void predict(double dt);

    /**
     * @brief update updates the Kalman filter
     * @param distance the measured distances to the landmarks
     * @return the weight of this particle after update (to be normalized!)
     */
    double update(double distance);
private:

    // Estimated position of the landmark
    Eigen::Vector3d mean;
    Eigen::Matrix3d covariance;

    // Todo: implement a way to get a jacobian of obs. model

    double pingerVariance;
};

#endif // KALMANFILTER_H
