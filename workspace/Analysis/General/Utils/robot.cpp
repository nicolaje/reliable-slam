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


void Robot::setPosition(double x, double y, double z)
{
    position[0]=x;
    position[1]=y;
    position[2]=z;
}


void Robot::toString()
{
    qDebug() << "Position: {" << position[0] << "," << position[1] << "," << position[2] << "}";
}
