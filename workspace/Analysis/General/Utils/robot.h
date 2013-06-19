#ifndef ROBOT_H
#define ROBOT_H
#include <string>
#include <sstream>
#include <vector>
#include <QDebug>
#include <ibex.h>
using namespace std;

class Robot
{
public:
    Robot();
    ~Robot();

    static const int NB_COLUMNS=15;
    /**
     * @brief SIGMA_FACTOR determines the confidence interval
     *  used to bound the noisy measurements.
     */
    static const int SIGMA_FACTOR=5;

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
    void setPosition(double vec[]);
    void setOrientation(double theta, double psi, double phi);
    void setOrientation(double vec[]);
    void setRotationSpeed(double dTheta, double dPsi, double dPhi);
    void setRotationSpeed(double vec[]);
    void setSpeed(double vx, double vy, double vz);
    void setSpeed(double vec[]);
    void setAcceleration(double ax, double ay, double az);
    void setAcceleration(double vec[]);
    void setLandmarksMeasurements(vector<double> meas);

    void setPositionNoisy(double x, double y, double z);
    void setPositionNoisy(double vec[]);
    void setOrientationNoisy(double theta, double psi, double phi);
    void setOrientationNoisy(double vec[]);
    void setRotationSpeedNoisy(double dTheta, double dPsi, double dPhi);
    void setRotationSpeedNoisy(double vec[]);
    void setSpeedNoisy(double vx, double vy, double vz);
    void setSpeedNoisy(double vec[]);
    void setAccelerationNoisy(double ax, double ay, double az);
    void setAccelerationNoisy(double vec[]);
    void setLandmarksMeasurementsNoisy(vector<double> meas);
    void toString();

    ibex::IntervalVector asIntervalVector();
    ibex::IntervalVector positionAsIntervalVector();
    ibex::IntervalVector orientationAsIntervalVector();
    ibex::IntervalVector angularSpeedAsIntervalVector();
    ibex::IntervalVector linearSpeedAsIntervalVector();
    ibex::IntervalVector accelerationAsIntervalVector();
private:

    /**
     * "Ground Truth" data
     */
    double position[3]={0,0,0};
    double orientation[3]={0,0,0};
    double angularSpeed[3]={0,0,0};
    double linearSpeed[3]={0,0,0};
    double acceleration[3]={0,0,0};

    vector<double> measurements;

    /**
     * Noisy data
     */
    double positionNoisy[3]={0,0,0};
    double orientationNoisy[3]={0,0,0};
    double angularSpeedNoisy[3]={0,0,0};
    double linearSpeedNoisy[3]={0,0,0};
    double accelerationNoisy[3]={0,0,0};

    vector<double> measurementsNoisy;

    /**
     * Noise parameters
     */
    double positionNoise[3]={0,0,0};
    double orientationNoise[3]={0,0,0};
    double angularSpeedNoise[3]={0,0,0};
    double linearSpeedNoise[3]={0,0,0};
    double accelerationNoise[3]={0,0,0};
    double measurementsNoise=0;
};

#endif // ROBOT_H
