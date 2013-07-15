#include "particle.h"
using namespace Eigen;

Particle::Particle(Vector3d robotPosition, Vector3d robotOrientation, Vector3d robotLinearMotion, Vector3d robotAngularMotion, std::vector<Vector3d> landmarksPosEstimates, std::vector<Matrix3d> landmarksPosCovs)
{
    this->robotPosition=robotPosition;
    this->robotOrientation=robotOrientation;
    this->robotLinearMotion=robotLinearMotion;
    this->robotAngularMotion=robotAngularMotion;
    for(int i=0; i<landmarksPosEstimates.size();i++){

    }
}

void Particle::setInitMap(std::vector<KalmanFilter> landmarksKFs)
{
    this->landmarksKalmanFilters=landmarksKFs;
}


void Particle::updateKF(double measurement, int landmarkIndex)
{
    weight=landmarksKalmanFilters[landmarkIndex].update(measurement);
}
