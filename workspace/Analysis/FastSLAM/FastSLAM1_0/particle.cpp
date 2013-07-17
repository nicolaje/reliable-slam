#include "particle.h"
using namespace Eigen;

Particle::Particle(Vector3d robotPosition, Vector3d robotOrientation, Vector3d robotLinearMotion, Vector3d robotAngularMotion, std::vector<Vector3d> landmarksPosEstimates, std::vector<Matrix3d> landmarksPosCovs)
{
    this->robotPosition=robotPosition;
    this->robotOrientation=robotOrientation;
    this->robotLinearMotion=robotLinearMotion;
    this->robotAngularMotion=robotAngularMotion;
    for(uint i=0; i<landmarksPosEstimates.size();i++){
        KalmanFilter f(landmarksPosEstimates[i],landmarksPosCovs[i]);
        landmarksKalmanFilters.push_back(f);
    }
}

void Particle::setInitMap(std::vector<KalmanFilter> landmarksKFs)
{
    this->landmarksKalmanFilters=landmarksKFs;
}

void Particle::predict(double dt)
{
    robotPosition=robotPosition+dt*getRotationMatrix(robotOrientation)*robotLinearMotion;
}


void Particle::updateKF(double measurement, int landmarkIndex)
{
    weight=landmarksKalmanFilters[landmarkIndex].update(measurement);
}


Matrix3d Particle::getRotationMatrix(Vector3d eulerZYX)
{
    Matrix3d rotation;
    double c1=cos(eulerZYX[0]),c2=cos(eulerZYX[1]),c3=cos(eulerZYX[2]);
    double s1=sin(eulerZYX[0]),s2=sin(eulerZYX[1]),s3=sin(eulerZYX[2]);
    rotation
            << c1*c2,c1*s2*s3-c3*s1,s1*s3+c1*c3*s2,\
            c2*s1,c1*c3+s1*s2*s3,c3*s1*s2-c1*s3,\
            -s2,c2*s3,c2*c3;

    return rotation;
}
