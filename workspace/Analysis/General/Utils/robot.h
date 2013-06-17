#ifndef ROBOT_H
#define ROBOT_H
#include <string>
#include <sstream>
#include <vector>
#include <QDebug>
using namespace std;

class Robot
{
public:
    Robot();
    ~Robot();

    static const int NB_COLUMNS=15;

    double* getPosition();
    double* getOrientation();
    double* getRotationSpeed();
    double* getSpeed();
    double* getAcceleration();
    vector<double> getLandmarksMeasurements();

    double* getPositionNoisy();
    double* getOrientationNoisy();
    double* getRotationSpeedNoisy();
    double* getSpeedNoisy();
    double* getAccelerationNoisy();
    vector<double> getLandmarksMeasurementsNoisy();

    int getLandmarksNumber();

    void setPosition(double x, double y, double z);
    void setOrientation(double theta, double psi, double phi);
    void setRotationSpeed(double dTheta, double dPsi, double dPhi);
    void setSpeed(double vx, double vy, double vz);
    void setAcceleration(double ax, double ay, double az);
    void setLandmarksMeasurements(vector<double> meas);

    void setPositionNoisy(double x, double y, double z);
    void setOrientationNoisy(double theta, double psi, double phi);
    void setRotationSpeedNoisy(double dTheta, double dPsi, double dPhi);
    void setSpeedNoisy(double vx, double vy, double vz);
    void setAccelerationNoisy(double ax, double ay, double az);
    void setLandmarksMeasurementsNoisy(vector<double> meas);
    void toString();
private:

    /**
     * "Ground Truth" data
     */
    double position[3]={0,0,0};
    double orientation[3]={0,0,0};
    double agularSpeed[3]={0,0,0};
    double linearSpeed[3]={0,0,0};
    double acceleration[3]={0,0,0};

    vector<double> measurements;

    /**
     * Noisy data
     */
    double positionNoisy[3]={0,0,0};
    double orientationNoisy[3]={0,0,0};
    double agularSpeedNoisy[3]={0,0,0};
    double linearSpeedNoisy[3]={0,0,0};
    double accelerationNoisy[3]={0,0,0};

    vector<double> measurementsNoisy;
};

#endif // ROBOT_H
