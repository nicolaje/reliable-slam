#ifndef PARTICLE_H
#include <eigen3/Eigen/Eigen>
#include <vector>
#include "kalmanfilter.h"
#define PARTICLE_H

/**
 * @brief The Particle class contains the position of the robot
 *for this particle and a Kalman Filter associated to each landmark for this particle.
 */
class Particle
{
public:
    static const uint WEIGHT_INDEP=0;
    static const uint WEIGHT_MULT=1;

    Particle(Eigen::Vector3d robotPosition, Eigen::Vector3d robotOrientation, Eigen::Vector3d robotLinearMotion, Eigen::Vector3d robotAngularMotion, int weightingMethond=WEIGHT_INDEP);
    void setInitMap(std::vector<KalmanFilter> landmarksKFs);
    void predict(double dt);
    void updateRobotPosition(Eigen::Vector3d position);
    void updateRobotOrientation(Eigen::Vector3d orientation);
    void updateRobotLinearMotion(Eigen::Vector3d linearMotion);
    void updateRobotOrientationMotion(Eigen::Vector3d orientationMotion);
    void updateRobotDepth(double depth);
    void updateKF(double measurement, int landmarkIndex);
    void updateAllKFs(std::vector<double> landmarksMeasurements);
    double getWeight();
    Eigen::Vector3d getPosition();
    Eigen::Vector3d getOrientation();
    std::vector<Eigen::Vector3d> getMap();

    void addMapError(Eigen::Vector3d error, uint landmarkIndex);

    void normalizeWeight(double norm);
private:
    double weight;
    int weightingMethod;
    Eigen::Vector3d robotPosition; // Position of the robot
    Eigen::Vector3d robotOrientation; // Orientation of the robot
    Eigen::Vector3d robotLinearMotion; // Linear speed of the robot
    Eigen::Vector3d robotAngularMotion; // Linear speed of the robot
    Eigen::Matrix3d getRotationMatrix(Eigen::Vector3d eulerZYX); // 3D Rotation matrix of the robot
    std::vector<KalmanFilter> landmarksKalmanFilters; // One Kalman Filter per landmark position
    std::vector<Eigen::Vector3d> path; // Robot Path
};

#endif // PARTICLE_H
