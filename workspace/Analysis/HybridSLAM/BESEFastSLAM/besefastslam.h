#ifndef BESEFASTSLAM_H
#include <ibex/ibex.h>
#include <eigen3/Eigen/Eigen>
#include "../../IntervalAnalysis/BoundedErrorStateEstimatorSLAM/bese.h"
#include "../../FastSLAM/FastSLAM1_0/fastslam.h"
#include "../../FastSLAM/FastSLAM1_0/particle.h"
#include <vector>
#define BESEFASTSLAM_H

class BESEFastSLAM
{
public:
    BESEFastSLAM(int particleNb, ibex::IntervalVector initState, int nbRobots, int nbLandmarks);

    void setPositionCovariance(Eigen::Matrix3d positionCovariance);
    void setOrientationCovariance(Eigen::Matrix3d orientationCovariance);
    void setLinearMotionCovariance(Eigen::Matrix3d linearMotionCovariance);
    void setAngularMotionCovariance(Eigen::Matrix3d angularMotionCovariance);
    void setPingerCovariance(double pingerVariance);

    void predict(ibex::Interval dt);
    void update(ibex::IntervalVector data);
private:
    BESE *beseEstimator;
    std::vector<Particle> particles;
    void reSample();

    Eigen::Matrix3d positionCovariance;
    Eigen::Matrix3d orientationCovariance;
    Eigen::Matrix3d linearMotionCovariance;
    Eigen::Matrix3d angularMotionCovariance;
    double pingerVariance;
    int particleNb;
};

#endif // BESEFASTSLAM_H
