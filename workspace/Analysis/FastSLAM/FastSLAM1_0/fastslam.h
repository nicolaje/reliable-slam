#ifndef FASTSLAM_H
#include <eigen3/Eigen/Eigen>
#include <vector>
#include "particle.h"
#include "kalmanfilter.h"
#define FASTSLAM_H

class FastSLAM
{
public:
    static const int RESAMPLE_EACH=0;
    static const int RESAMPLE_ALL=1; // Resample after one landmark has been incorporated in every particle
    static const int RESAMPLE_EVERYTIME=2; // Resample for each landmark measurement incorpored, for each particle (resource consuming!!)
    static const int RESAMPLE_ALL_AT_ONCE=4;
    static const int ROULETTE=0;
    static const int ROULETTE_1ST_QUARTIL=1;
    static const int ROULETTE_2ST_QUARTIL=2;
    static const int ROULETTE_3ST_QUARTIL=3;
    static const int ROULETTE_PERCENTIL=4;

    static std::default_random_engine generator;
    static std::vector<Eigen::Vector3d> drawSamples(int nb, Eigen::Vector3d mean, Eigen::Matrix3d covariance);

    FastSLAM(Eigen::Matrix3d positionCovariance, Eigen::Matrix3d orientationCovariance, Eigen::Matrix3d linearMotionCovariance,Eigen::Matrix3d angularMotionCovariance, double pingerVariance,uint RESAMPLE_METHOD=RESAMPLE_ALL_AT_ONCE,uint RESAMPLE_STRATEGY=ROULETTE, int percentil=25);
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
    void updateRobotDepth(double depth);

    /**
     * @brief updateRobotState updates the orientation of the robot in each particle by sampling from a normal distribution centered on the given vector and covariance matrix.
     * @param orientation
     */
    void updateRobotOrientation(Eigen::Vector3d orientation);
    void updateRobotMotion(Eigen::Vector3d linearMotion, Eigen::Vector3d angularMotion);

    void updateMap(std::vector<double> landmarksMeasurements);

    std::vector<Particle> reSample();
    void setPercentilResampling(int percentil);

    void setErrorCovariance(Eigen::Matrix3d errorCovariance);

    Particle getBestParticle();
    void normalize();
private:
    Eigen::Matrix3d errorCovariance;

    Eigen::Matrix3d positionCovariance;
    Eigen::Matrix3d orientationCovariance;
    Eigen::Matrix3d linearMotionCovariance;
    Eigen::Matrix3d angularMotionCovariance;
    double pingerVariance;
    int particleNb;
    int resampling_method;
    int resampling_strategy;
    int percentil;

    std::vector<Particle> particles;
};

#endif // FASTSLAM_H
