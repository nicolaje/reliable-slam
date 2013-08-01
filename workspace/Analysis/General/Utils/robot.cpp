#include "robot.h"

Robot::Robot()
{
    pingerMeasurements;
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
    return this->orientation;
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
    pingerMeasurements.clear();
    pingerMeasurements.insert(pingerMeasurements.end(),meas.begin(),meas.end());
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
    qDebug() << "===========================================================";
    qDebug() << "True data: ";
    qDebug() << "Position: {" << position[0] << "," << position[1] << "," << position[2] << "}\n"
             << "Orientation: {" << orientation[0] <<","<<orientation[1]<<","<<orientation[2]<<"}\n"
             << "Ang. Speed: {"<< angularSpeed[0] <<","<<angularSpeed[1]<<","<<angularSpeed[2]<<"}\n"
             << "Acceleration: {"<<acceleration[0]<<","<<acceleration[1]<<","<<acceleration[2]<<"}\n";
    for(int i=0;i<pingerMeasurements.size();i++){
        qDebug() << "Meas. nb "<<i<<": "<<pingerMeasurements.at(i);
    }
    qDebug() << "===========================================================";
    qDebug() << "Noisy data:";
    qDebug() << "Position: {" << positionNoisy[0] << "," << positionNoisy[1] << "," << positionNoisy[2] << "}\n"
             << "Orientation: {" << orientationNoisy[0] <<","<<orientationNoisy[1]<<","<<orientationNoisy[2]<<"}\n"
             << "Ang. Speed: {"<< angularSpeedNoisy[0] <<","<<angularSpeedNoisy[1]<<","<<angularSpeedNoisy[2]<<"}\n"
             << "Acceleration: {"<<accelerationNoisy[0]<<","<<accelerationNoisy[1]<<","<<accelerationNoisy[2]<<"}\n";
    for(int i=0;i<pingerMeasurements.size();i++){
        qDebug() << "Meas. nb "<<i<<": "<< pingerMeasurements.at(i);
    }
}

ibex::IntervalVector Robot::asIntervalVector()
{
    ibex::IntervalVector res(NB_COLUMNS);
    res[0]=ibex::Interval(-SIGMA_FACTOR*positionNoise[0]+positionNoisy[0],SIGMA_FACTOR*positionNoise[0]+positionNoisy[0]);
    res[1]=ibex::Interval(-SIGMA_FACTOR*positionNoise[1]+positionNoisy[1],SIGMA_FACTOR*positionNoise[1]+positionNoisy[1]);
    res[2]=ibex::Interval(-SIGMA_FACTOR*positionNoise[2]+positionNoisy[2],SIGMA_FACTOR*positionNoise[2]+positionNoisy[2]);
    res[3]=ibex::Interval(-SIGMA_FACTOR*orientationNoise[0]+orientationNoisy[0],SIGMA_FACTOR*orientationNoise[0]+orientationNoisy[0]);
    res[4]=ibex::Interval(-SIGMA_FACTOR*orientationNoise[1]+orientationNoisy[1],SIGMA_FACTOR*orientationNoise[1]+orientationNoisy[1]);
    res[5]=ibex::Interval(-SIGMA_FACTOR*orientationNoise[2]+orientationNoisy[2],SIGMA_FACTOR*orientationNoise[2]+orientationNoisy[2]);
    res[6]=ibex::Interval(-SIGMA_FACTOR*angularSpeedNoise[0]+angularSpeedNoisy[0],SIGMA_FACTOR*angularSpeedNoise[0]+angularSpeedNoisy[0]);
    res[7]=ibex::Interval(-SIGMA_FACTOR*angularSpeedNoise[1]+angularSpeedNoisy[1],SIGMA_FACTOR*angularSpeedNoise[1]+angularSpeedNoisy[1]);
    res[8]=ibex::Interval(-SIGMA_FACTOR*angularSpeedNoise[2]+angularSpeedNoisy[2],SIGMA_FACTOR*angularSpeedNoise[2]+angularSpeedNoisy[2]);
    res[9]=ibex::Interval(-SIGMA_FACTOR*linearSpeedNoise[0]+linearSpeedNoisy[0],SIGMA_FACTOR*linearSpeedNoise[0]+linearSpeedNoisy[0]);
    res[10]=ibex::Interval(-SIGMA_FACTOR*linearSpeedNoise[1]+linearSpeedNoisy[1],SIGMA_FACTOR*linearSpeedNoise[1]+linearSpeedNoisy[1]);
    res[11]=ibex::Interval(-SIGMA_FACTOR*linearSpeedNoise[2]+linearSpeedNoisy[2],SIGMA_FACTOR*linearSpeedNoise[2]+linearSpeedNoisy[2]);
    res[12]=ibex::Interval(-SIGMA_FACTOR*accelerationNoise[0]+accelerationNoisy[0],SIGMA_FACTOR*accelerationNoise[0]+accelerationNoisy[0]);
    res[13]=ibex::Interval(-SIGMA_FACTOR*accelerationNoise[1]+accelerationNoisy[1],SIGMA_FACTOR*accelerationNoise[1]+accelerationNoisy[1]);
    res[14]=ibex::Interval(-SIGMA_FACTOR*accelerationNoise[2]+accelerationNoisy[2],SIGMA_FACTOR*accelerationNoise[2]+accelerationNoisy[2]);
    return res;
}

ibex::IntervalVector Robot::positionAsIntervalVector()
{
    ibex::IntervalVector res(3);
    res[0]=ibex::Interval(-SIGMA_FACTOR*positionNoise[0]+positionNoisy[0],SIGMA_FACTOR*positionNoise[0]+positionNoisy[0]);
    res[1]=ibex::Interval(-SIGMA_FACTOR*positionNoise[1]+positionNoisy[1],SIGMA_FACTOR*positionNoise[1]+positionNoisy[1]);
    res[2]=ibex::Interval(-SIGMA_FACTOR*positionNoise[2]+positionNoisy[2],SIGMA_FACTOR*positionNoise[2]+positionNoisy[2]);
    return res;
}

ibex::IntervalVector Robot::orientationAsIntervalVector()
{
    ibex::IntervalVector res(3);
    for(int i=0;i<3;i++){
        res[i]=ibex::Interval(-SIGMA_FACTOR*orientationNoise[i]+orientationNoisy[i],SIGMA_FACTOR*orientationNoise[i]+orientationNoisy[i]);
    }
    return res;
}

ibex::IntervalVector Robot::angularSpeedAsIntervalVector()
{
    ibex::IntervalVector res(3);
    for(int i=0; i<3; i++){
        res[i]=ibex::Interval(-SIGMA_FACTOR*angularSpeedNoise[i]+angularSpeedNoisy[i],SIGMA_FACTOR*angularSpeedNoise[i]+angularSpeedNoisy[i]);
    }
    return res;
}

ibex::IntervalVector Robot::linearSpeedAsIntervalVector()
{
    ibex::IntervalVector res(3);
    for(int i=0; i<3; i++){
        res[i]=ibex::Interval(-SIGMA_FACTOR*linearSpeedNoise[i]+linearSpeedNoisy[i],SIGMA_FACTOR*linearSpeedNoise[i]+linearSpeedNoisy[i]);
    }
    return res;
}

ibex::IntervalVector Robot::accelerationAsIntervalVector()
{
    ibex::IntervalVector res(3);
    for(int i=0; i<3; i++){
        res[i]=ibex::Interval(-SIGMA_FACTOR*accelerationNoise[i]+accelerationNoisy[i],SIGMA_FACTOR*accelerationNoise[i]+accelerationNoisy[i]);
    }
    return res;
}

/**
 * @brief Robot::measurementsAsIntervalVector TODO remove, returns only the pinger measurements
 * @return
 */
ibex::IntervalVector Robot::pingerMeasurementsAsIntervalVector()
{
    ibex::IntervalVector res(this->measurementsNoisy.size()); //  TODO put measurementnoisy instead of all the pingerMeasurements
    for(int i=0;i<this->measurementsNoisy.size();i++){
        res[i]=ibex::Interval(-SIGMA_FACTOR*pingerNoise+this->measurementsNoisy.at(i),this->measurementsNoisy.at(i)+pingerNoise*SIGMA_FACTOR);
    }
    return res;
}



vector<double> Robot::getLandmarksMeasurements()
{
    return this->pingerMeasurements;
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

int Robot::getLandmarksNumber()
{
    return this->pingerMeasurements.size();
}

ibex::IntervalVector Robot::getObservationsAsIntervalVector()
{
    ibex::IntervalVector *res=new ibex::IntervalVector(12+this->getLandmarksNumber());
    for(int i=0; i<3; i++){
        (*res)[i]=positionAsIntervalVector()[i];
        (*res)[3+i]=orientationAsIntervalVector()[i];
        (*res)[6+i]=linearSpeedAsIntervalVector()[i];
        (*res)[9+i]=angularSpeedAsIntervalVector()[i];
    }
    for(int i=0; i<getLandmarksNumber(); i++){
        (*res)[12+i]=pingerMeasurementsAsIntervalVector()[i];
    }
    return res;
}

string Robot::groundTruthToString()
{
    std::string res;
    std::ostringstream ss;
    for(int i=0; i<3; i++){
        ss << position[i] <<";";
    }
    for(int i=0; i<3; i++){
        ss << orientation[i] <<";";
    }
    for(int i=0; i<3; i++){
        ss << linearSpeed[i] <<";";
    }
    for(int i=0; i<3; i++){
        ss << angularSpeed[i] <<";";
    }
    res=ss.str();
    return res+"\n";
}

Eigen::Vector3d Robot::positionAsVect()
{
    Eigen::Vector3d positionAsVect;
    positionAsVect << positionNoisy[0],positionNoisy[1],positionNoisy[2];
    return positionAsVect;
}

Eigen::Vector3d Robot::orientationAsVect()
{
    Eigen::Vector3d orientationAsVect;
    orientationAsVect << orientationNoisy[0],orientationNoisy[1],orientationNoisy[2];
    return orientationAsVect;
}

Eigen::Vector3d Robot::linearMotionAsVect()
{
    Eigen::Vector3d linearMotionAsVect;
    linearMotionAsVect << linearSpeedNoisy[0],linearSpeedNoisy[1],linearSpeedNoisy[2];
    return linearMotionAsVect;
}



Eigen::Vector3d Robot::angularMotionAsVect()
{
    Eigen::Vector3d angularMotionAsVect;
    angularMotionAsVect << angularSpeedNoisy[0],angularSpeedNoisy[1],angularSpeedNoisy[2];
    return angularMotionAsVect;
}


Eigen::Vector3d Robot::positionTrueAsVect()
{
    Eigen::Vector3d positionTrue;
    positionTrue << position[0],position[1],position[2];
    return positionTrue;
}

Eigen::Vector3d Robot::orientationTrueAsVect()
{
    Eigen::Vector3d orientationTrue;
    orientationTrue << orientation[0],orientation[1],orientation[2];
    return orientationTrue;
}

Eigen::Vector3d Robot::linearMotionTrueAsVect()
{
    Eigen::Vector3d linearMotionTrue;
    linearMotionTrue << linearSpeed[0],linearSpeed[1],linearSpeed[2];
    return linearMotionTrue;
}


Eigen::Vector3d Robot::angularMotionTrueAsVect()
{
    Eigen::Vector3d angularMotionTrue;
    angularMotionTrue << angularSpeed[0],angularSpeed[1],angularSpeed[2];
    return angularMotionTrue;
}
