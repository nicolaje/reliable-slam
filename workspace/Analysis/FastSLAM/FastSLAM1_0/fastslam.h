#ifndef FASTSLAM_H
#define FASTSLAM_H
#include <eigen3/Eigen/Eigen>
#include <vector>
#include "particle.h"

class FastSLAM
{
public:
    FastSLAM(Eigen::Matrix3d positionCovariance, Eigen::Matrix3d orientationCovariance, Eigen::Matrix3d linearMotionCovariance,Eigen::Matrix3d angularMotionCovariance, double pingerVariance);
    /**
     * @brief initParticles Draws a particle swarm from the initial estimation of the robot & landmarks positions.
     * @param landmarksPosEstimates
     * @param landmarksCovEstimates
     */
    void initParticles(Eigen::Vector3d robotPosition, std::vector<Eigen::Vector3d> landmarksPosEstimates, std::vector<Eigen::Matrix3d> landmarksCovEstimates);
private:
    Eigen::Matrix3d positionCovariance;
    Eigen::Matrix3d orientationCovariance;
    Eigen::Matrix3d linearMotionCovariance;
    Eigen::Matrix3d angularMotionCovariance;
    double pingerVariance;

    std::vector<Particle> particles;
};

#endif // FASTSLAM_H
