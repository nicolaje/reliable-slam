#include "robot.h"

Robot::Robot()
{
    measurements;
}

Robot::~Robot()
{

}

double *Robot::getPosition()
{
    return position;
}

double *Robot::getOrientation()
{
    return this->position;
}

double *Robot::getRotationSpeed()
{
    return this->angularSpeed;
}

double *Robot::getSpeed()
{
    return this->linearSpeed;
}

double *Robot::getAcceleration()
{
    return this->acceleration;
}


void Robot::setPosition(double x, double y, double z)
{
    position[0]=x;
    position[1]=y;
    position[2]=z;
}

void Robot::setPosition(double vec[])
{
    this->setPosition(vec[0],vec[1],vec[2]);
}

void Robot::setOrientation(double theta, double psi, double phi)
{
    orientation[0]=theta;
    orientation[1]=psi;
    orientation[2]=phi;
}

void Robot::setOrientation(double vec[])
{
    setOrientation(vec[0],vec[1],vec[2]);
}

void Robot::setRotationSpeed(double dTheta, double dPsi, double dPhi)
{
    angularSpeed[0]=dTheta;
    angularSpeed[1]=dPsi;
    angularSpeed[2]=dPhi;
}

void Robot::setRotationSpeed(double vec[])
{
    setRotationSpeed(vec[0],vec[1],vec[2]);
}

void Robot::setSpeed(double vx, double vy, double vz)
{
    linearSpeed[0]=vx;
    linearSpeed[1]=vy;
    linearSpeed[2]=vz;
}

void Robot::setSpeed(double vec[])
{
    setSpeed(vec[0],vec[1],vec[2]);
}

void Robot::setAcceleration(double ax, double ay, double az)
{
    acceleration[0]=ax;
    acceleration[1]=ay;
    acceleration[2]=az;
}

void Robot::setAcceleration(double vec[])
{
    setAcceleration(vec[0],vec[1],vec[2]);
}

void Robot::setLandmarksMeasurements(vector<double> meas)
{
    measurements.clear();
    measurements.insert(measurements.end(),meas.begin(),meas.end());
}

void Robot::setPositionNoisy(double x, double y, double z)
{
    positionNoisy[0]=x;
    positionNoisy[1]=y;
    positionNoisy[2]=z;
}

void Robot::setPositionNoisy(double vec[])
{
    setPositionNoisy(vec[0],vec[1],vec[2]);
}

void Robot::setOrientationNoisy(double theta, double psi, double phi)
{
    orientationNoisy[0]=theta;
    orientationNoisy[1]=psi;
    orientationNoisy[2]=phi;
}

void Robot::setOrientationNoisy(double vec[])
{
    setOrientationNoisy(vec[0],vec[1],vec[2]);
}

void Robot::setRotationSpeedNoisy(double dTheta, double dPsi, double dPhi)
{
    angularSpeedNoisy[0]=dTheta;
    angularSpeedNoisy[1]=dPsi;
    angularSpeedNoisy[2]=dPhi;
}

void Robot::setRotationSpeedNoisy(double vec[])
{
    setRotationSpeedNoisy(vec[0],vec[1],vec[2]);
}

void Robot::setSpeedNoisy(double vx, double vy, double vz)
{
    linearSpeedNoisy[0]=vx;
    linearSpeedNoisy[1]=vy;
    linearSpeedNoisy[2]=vz;
}

void Robot::setSpeedNoisy(double vec[])
{
    setSpeedNoisy(vec[0],vec[1],vec[2]);
}

void Robot::setAccelerationNoisy(double ax, double ay, double az)
{
    accelerationNoisy[0]=ax;
    accelerationNoisy[1]=ay;
    accelerationNoisy[2]=az;
}

void Robot::setAccelerationNoisy(double vec[])
{
    setAccelerationNoisy(vec[0],vec[1],vec[2]);
}

void Robot::setLandmarksMeasurementsNoisy(vector<double> meas)
{
    measurementsNoisy.clear();
    measurementsNoisy.insert(measurementsNoisy.begin(),meas.begin(),meas.end());
}


void Robot::toString()
{
    qDebug() << "True data: ";
    qDebug() << "Position: {" << position[0] << "," << position[1] << "," << position[2] << "}\n"
             << "Orientation: {" << orientation[0] <<","<<orientation[1]<<","<<orientation[2]<<"}\n"
             << "Ang. Speed: {"<< angularSpeed[0] <<","<<angularSpeed[1]<<","<<angularSpeed[2]<<"}\n"
             << "Acceleration: {"<<acceleration[0]<<","<<acceleration[1]<<","<<acceleration[2]<<"}\n";
    for(int i=0;i<measurements.size();i++){
        qDebug() << "Meas. nb "<<i<<": "<<measurements.at(i);
    }
    qDebug() << "Noisy data:";
    qDebug() << "Position: {" << positionNoisy[0] << "," << positionNoisy[1] << "," << positionNoisy[2] << "}\n"
             << "Orientation: {" << orientationNoisy[0] <<","<<orientationNoisy[1]<<","<<orientationNoisy[2]<<"}\n"
             << "Ang. Speed: {"<< angularSpeedNoisy[0] <<","<<angularSpeedNoisy[1]<<","<<angularSpeedNoisy[2]<<"}\n"
             << "Acceleration: {"<<accelerationNoisy[0]<<","<<accelerationNoisy[1]<<","<<accelerationNoisy[2]<<"}\n";
    for(int i=0;i<measurements.size();i++){
        qDebug() << "Meas. nb "<<i<<": "<< measurements.at(i);
    }
}


vector<double> Robot::getLandmarksMeasurements()
{
    return this->measurements;
}

double *Robot::getPositionNoisy()
{
    return this->positionNoisy;
}

double *Robot::getOrientationNoisy()
{
    return this->orientationNoisy;
}

double *Robot::getRotationSpeedNoisy()
{
    return this->angularSpeedNoisy;
}

double *Robot::getSpeedNoisy()
{
    return this->linearSpeedNoisy;
}

double *Robot::getAccelerationNoisy()
{
    return this->accelerationNoisy;
}

vector<double> Robot::getLandmarksMeasurementsNoisy()
{
    return this->measurementsNoisy;
}
