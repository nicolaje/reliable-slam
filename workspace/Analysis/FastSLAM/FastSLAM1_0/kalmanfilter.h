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
    static Eigen::Matrix<double,3,3> ID3D;
    KalmanFilter(Eigen::Vector3d mean, Eigen::Matrix3d covariance, double pingerVariance);
    void predict(double dt);

    Eigen::Vector3d getMean();
    void setMean(Eigen::Vector3d mean);

    /**
     * @brief update updates the Kalman filter
     * @param distance the measured distances to the landmarks
     * @return the weight of this particle after update (to be normalized!)
     */
    double update(double distance, Eigen::Vector3d robotPos);
private:

    // Estimated position of the landmark
    Eigen::Vector3d mean;
    Eigen::Matrix3d covariance;

    double observation(Eigen::Vector3d robotPosition);
    // Todo: implement a way to get a jacobian of obs. model
    Eigen::RowVector3d jacobianObservationModel(Eigen::Vector3d robotPosition);

    double pingerVariance;
};

#endif // KALMANFILTER_H
