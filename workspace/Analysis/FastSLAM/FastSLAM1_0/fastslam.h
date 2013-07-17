#ifndef FASTSLAM_H
#include <eigen3/Eigen/Eigen>
#include <vector>
#include "particle.h"
#include "kalmanfilter.h"
#define FASTSLAM_H

class FastSLAM
{
public:
    static const uint RESAMPLE_EACH=0;
    static const uint RESAMPLE_ALL=1; // Resample after one landmark has been incorporated in every particle
    static const uint RESAMPLE_EVERYTIME=2; // Resample for each landmark measurement incorpored, for each particle (resource consuming!!)
    static const uint ROULETTE=0;
    static const uint ROULETTE_1ST_QUARTIL=1;
    static const uint ROULETTE_2ST_QUARTIL=2;
    static const uint ROULETTE_3ST_QUARTIL=3;
    static const uint ROULETTE_PERCENTIL=4;

    FastSLAM(Eigen::Matrix3d positionCovariance, Eigen::Matrix3d orientationCovariance, Eigen::Matrix3d linearMotionCovariance,Eigen::Matrix3d angularMotionCovariance, double pingerVariance,uint RESAMPLE_METHOD=RESAMPLE_EACH,uint RESAMPLE_STRATEGY=ROULETTE, int percentil=25);
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
    void handleReSampling();
    void setPercentilResampling(int percentil);
private:
    Eigen::Matrix3d positionCovariance;
    Eigen::Matrix3d orientationCovariance;
    Eigen::Matrix3d linearMotionCovariance;
    Eigen::Matrix3d angularMotionCovariance;
    double pingerVariance;
    int particleNb;
    int resampling_method;
    int resampling_strategy;
    int percentil;

    void normalize();
    std::vector<Particle> particles;
};

#endif // FASTSLAM_H
