#ifndef PARTICLE_H
#define PARTICLE_H
#include <eigen3/Eigen/Eigen>
#include <vector>
#include "kalmanfilter.h"

/**
 * @brief The Particle class contains the position of the robot
 *for this particle and a Kalman Filter associated to each landmark for this particle.
 */
class Particle
{
public:
    Particle(Eigen::Vector3d robotPosition, Eigen::Vector3d robotOrientation, Eigen::Vector3d robotLinearMotion, Eigen::Vector3d robotAngularMotion, std::vector<Eigen::Vector3d> landmarksPosEstimates, std::vector<Eigen::Matrix3d> landmarksPosCovs);
    void setInitMap(std::vector<KalmanFilter> landmarksKFs);
    void predict(double dt);
    void updateRobotPosition(Eigen::Vector3d position);
    void updateRobotOrientation(Eigen::Vector3d orientation);
    void updateRobotLinearMotion(Eigen::Vector3d linearMotion);
    void updateRobotOrientationMotion(Eigen::Vector3d orientationMotion);
    void updateKF(double measurement, int landmarkIndex);
    double getWeight();
private:
    double weight;
    Eigen::Vector3d robotPosition; // Position of the robot
    Eigen::Vector3d robotOrientation; // Orientation of the robot
    Eigen::Vector3d robotLinearMotion; // Linear speed of the robot
    Eigen::Vector3d robotAngularMotion; // Linear speed of the robot
    Eigen::Matrix3d getRotationMatrix(Eigen::Vector3d eulerZYX); // 3D Rotation matrix of the robot
    std::vector<KalmanFilter> landmarksKalmanFilters; // One Kalman Filter per landmark position
};

#endif // PARTICLE_H
