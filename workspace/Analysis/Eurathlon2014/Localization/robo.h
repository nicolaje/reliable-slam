#ifndef ROBO_H
#define ROBO_H

#include <iostream>
#include <QVector>
#include "configuracaoes.h"
#include "landmark.h"

class Hybrid;

class Robo
{
public:
    QVector <xyz> mPose;
    QVector <xyz> mGPS;
    QVector <xyz> mGyrocompass;
    QVector <xyz> mLinearAcceleration;
    QVector <xyz> mAngularVelocity;
    QVector <xyz> mLinearVelocity;
    QVector <double> mDeep;
    QVector < QVector <Landmark> > mLandmarks;

    clock_t mCurrentTime, mLastEstimation;

    Hybrid *mLocalizationSystem;
    int curTime;

    Robo();
    ~Robo();
    void setAccelerometer(xyz accelerometer);
    xyz getAccelerometer();

    void setLinearVelocity(xyz linearVelocity);
    xyz getLinearVelocity();

    void setLandmarks(QVector <Landmark> landmarks);
    QVector <Landmark> getLandmarks();

    void setDeep(double deep);
    double getDeep();

    void setGPS(xyz gps);
    QVector<double> getGPS();

    void setGyroscope(xyz gyroscope);
    xyz getGyroscope();

    void setGyrocompass(xyz gyrocompass);
    xyz getGyrocompass();

    xyz getDeltaHeading();

    double getElapsedTime();

    void setSensors(xyz accelerometer,xyz linearVelocity,QVector <Landmark> landmarks, double deep,xyz gps,xyz gyroscope,xyz gyrocompass);

    std::string toString();
    void runSimlutatedData();
    void findYourself();
};

#include "hybrid.h"

#endif // ROBO_H
