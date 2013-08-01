#ifndef EKFSLAM_H
#include <eigen3/Eigen/Eigen>
#define EKFSLAM_H

class EKFSlam
{
public:
    EKFSlam(int robotsNb, int landmarksNb);

    void predict(double dt);
    void update(Eigen::Vectorxd observations);

    void setPositionCovariance(Eigen::Matrix3d positionCovariance);
    void setOrientationCovariance(Eigen::Matrix3d orientationCovariance);
    void setLinearMotionCovariance(Eigen::Matrix3d linearMotionCovariance);
    void setAngularMotionCovariance(Eigen::Matrix3d motionCovariance);
    void setPingerCovariance(double pingerCovariance);
private:
    Eigen::Vectorxd stateVector;
    Eigen::Matrix3d positionCovariance;
    Eigen::Matrix3d orientationCovariance;
    Eigen::Matrix3d linearMotionCovariance;
    Eigen::Matrix3d angularMotionCovariance;
    double pingerCovariance;
};

#endif // EKFSLAM_H
