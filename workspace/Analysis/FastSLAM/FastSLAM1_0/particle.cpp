#include "particle.h"
#include "fastslam.h"
#include "../../General/Utils/utils.h"
#include <iostream>
using namespace Eigen;

Particle::Particle(Vector3d robotPosition, Vector3d robotOrientation, Vector3d robotLinearMotion, Vector3d robotAngularMotion,int weightingMethod)
{
    this->weight=1;
    this->robotPosition=robotPosition;
    this->robotOrientation=robotOrientation;
    this->robotLinearMotion=robotLinearMotion;
    this->robotAngularMotion=robotAngularMotion;
    this->weightingMethod=weightingMethod;
}

void Particle::setInitMap(std::vector<KalmanFilter> landmarksKFs)
{
    this->landmarksKalmanFilters=landmarksKFs;
}

void Particle::predict(double dt)
{
    robotPosition=robotPosition+dt*getRotationMatrix(robotOrientation)*robotLinearMotion;
    for(uint l=0;l<landmarksKalmanFilters.size();l++){
        landmarksKalmanFilters[l].predict(dt);
    }
}

void Particle::updateKF(double measurement, int landmarkIndex)
{
    switch(weightingMethod){
    case WEIGHT_INDEP:
        weight=landmarksKalmanFilters[landmarkIndex].update(measurement,robotPosition);
        break;
    case WEIGHT_MULT:
        weight*=landmarksKalmanFilters[landmarkIndex].update(measurement,robotPosition);
        break;
    }
}

void Particle::updateAllKFs(std::vector<double> landmarksMeasurements)
{
    this->weight=1;
    for(int i=0;i<landmarksKalmanFilters.size();i++){
        this->weight*=landmarksKalmanFilters[i].update(landmarksMeasurements[i],robotPosition);
    }
}

double Particle::getWeight()
{
    return weight;
}

void Particle::shakeMap(std::vector<ibex::IntervalVector> mapBox)
{
    for(int i=0;i<this->landmarksKalmanFilters;i++){
        KalmanFilter k=landmarksKalmanFilters[i];
        k.setMean(FastSLAM::drawSamples(1,mapBox[i])[0]);
        k.setCovariance(Utils::boxToCovarianceMatrix(mapBox[i],3));
        landmarksKalmanFilters[i]=k;
    }
}

Vector3d Particle::getPosition()
{
    return robotPosition;
}


Matrix3d Particle::getRotationMatrix(Vector3d eulerZYX)
{
    Matrix3d rotation;
    double c1=cos(eulerZYX[2]),c2=cos(eulerZYX[1]),c3=cos(eulerZYX[0]);
    double s1=sin(eulerZYX[2]),s2=sin(eulerZYX[1]),s3=sin(eulerZYX[0]);
    rotation
            << c1*c2,c1*s2*s3-c3*s1,s1*s3+c1*c3*s2,\
            c2*s1,c1*c3+s1*s2*s3,c3*s1*s2-c1*s3,\
            -s2,c2*s3,c2*c3;

    return rotation;
}


void Particle::normalizeWeight(double norm)
{
    weight/=norm;
}

void Particle::updateRobotPosition(Vector3d position)
{
    this->robotPosition=position;
}

void Particle::updateRobotOrientation(Vector3d orientation)
{
    this->robotOrientation=orientation;
}

void Particle::updateRobotLinearMotion(Vector3d linearMotion)
{
    this->robotLinearMotion=linearMotion;
}

void Particle::updateRobotOrientationMotion(Vector3d orientationMotion)
{
    this->robotAngularMotion=orientationMotion;
}

void Particle::updateRobotDepth(double depth)
{
    this->robotPosition[2]=depth;
}


Vector3d Particle::getOrientation()
{
    return robotOrientation;
}

std::vector<Vector3d> Particle::getMap()
{
    std::vector<Vector3d> map;
    for(int i=0;i<landmarksKalmanFilters.size();i++){
        map.push_back(landmarksKalmanFilters[i].getMean());
    }
    return map;
}

VectorXd Particle::toVector()
{
    VectorXd res(6+3*landmarksKalmanFilters.size());
    for(int i=0;i<3;i++){
        res[i]=getPosition()[i];
        res[3+i]=getOrientation()[i];
        for(int j=0;j<landmarksKalmanFilters.size();j++){
            res[6+3*j+i]=landmarksKalmanFilters[j].getMean()[i];
        }
    }
    return res;
}

void Particle::addMapError(Vector3d error, uint landmarkIndex)
{
    Vector3d lmPos=landmarksKalmanFilters[landmarkIndex].getMean();
    landmarksKalmanFilters[landmarkIndex].setMean((lmPos+error));
}
