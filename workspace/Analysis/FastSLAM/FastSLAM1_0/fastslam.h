#ifndef FASTSLAM_H
#define FASTSLAM_H
#include <eigen3/Eigen/Eigen>
#include <vector>
#include "particle.h"
#include "kalmanfilter.h"

class FastSLAM
{
public:
    FastSLAM(Eigen::Matrix3d positionCovariance, Eigen::Matrix3d orientationCovariance, Eigen::Matrix3d linearMotionCovariance,Eigen::Matrix3d angularMotionCovariance, double pingerVariance);
    /**
     * @brief initParticles Draws a particle swarm from the initial estimation of the robot & landmarks positions.
     * @param landmarksPosEstimates
     * @param landmarksCovEstimates
     */
    void initParticles(int particleNb,Eigen::Vector3d robotPosition, Eigen::Vector3d robotOrientation, Eigen::Vector3d robotLinearMotion, Eigen::Vector3d robotAngularMotion, std::vector<Eigen::Vector3d> landmarksPosEstimates, std::vector<Eigen::Matrix3d> landmarksCovEstimates);
    void predict(double dt);
    /**
     * @brief updateRobotState updates the position of the robot in each particle, by sampling from a normal distribution centered on the given vector with the provided increased covariance matrix. Used when GPS is measued.
     * @param position
     * @param orientation
     */
    void updateRobotPosition(Eigen::Vector3d position);
    /**
     * @brief updateRobotState updates the orientation of the robot in each particle by sampling from a normal distribution centered on the given vector and covariance matrix.
     * @param orientation
     */
    void updateRobotOrientation(Eigen::Vector3d orientation);
    void updateRobotMotion(Eigen::Vector3d linearMotion, Eigen::Vector3d angularMotion);
    void updateMap(std::vector<double> landmarksMeasurements);
private:
    Eigen::Matrix3d positionCovariance;
    Eigen::Matrix3d orientationCovariance;
    Eigen::Matrix3d linearMotionCovariance;
    Eigen::Matrix3d angularMotionCovariance;
    double pingerVariance;
    int particleNb;

    std::vector<Particle> particles;
};

#endif // FASTSLAM_H
