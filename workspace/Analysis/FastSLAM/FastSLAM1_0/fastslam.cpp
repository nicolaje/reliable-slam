#include "fastslam.h"
using namespace Eigen;
FastSLAM::FastSLAM(Matrix3d positionCovariance, Matrix3d orientationCovariance, Matrix3d linearMotionCovariance, Matrix3d angularMotionCovariance, double pingerVariance)
{
    this->positionCovariance=positionCovariance;
    this->orientationCovariance=orientationCovariance;
    this->linearMotionCovariance=linearMotionCovariance;
    this->angularMotionCovariance=angularMotionCovariance;
    this->pingerVariance=pingerVariance;
}

void FastSLAM::initParticles(Vector3d robotPosition, std::vector<Vector3d> landmarksPosEstimates, std::vector<Matrix3d> landmarksCovEstimates)
{
    // TODO: find a way to draw landmark positions from a multivariate normal distribution.
    // But for now, drawing from uniform distribution, and doing it wrong because assuming the cov are diagonals!
}
