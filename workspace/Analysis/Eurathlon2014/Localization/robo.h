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
    QVector <xyz> mTruePose;
    QVector <xyz> mGyrocompass;
    QVector <xyz> mLinearAcceleration;
    QVector <xyz> mAngularVelocity;
    QVector <xyz> mLinearVelocity;
    QVector <double> mDeep;

    clock_t mGPSTime, mLandmarkTime;
    QVector <xyz> mGPS;
    QVector < QVector <Landmark> > mLandmarks;

    clock_t mCurrentTime, mLastEstimation;

    Hybrid *mLocalizationSystem;

    Robo();
    ~Robo();
    void setPose(xyz pose);
    xyz getPose();

    void setTruePose(xyz truePose);
    xyz getTruePose();

    void setAccelerometer(xyz accelerometer);
    xyz getAccelerometer();

    void setLinearVelocity(xyz linearVelocity);
    xyz getLinearVelocity();

    void setDeep(double deep);
    double getDeep();

    void setGyroscope(xyz gyroscope);
    xyz getGyroscope();

    void setGyrocompass(xyz gyrocompass);
    xyz getGyrocompass();

    xyz getDeltaHeading();

    void setLandmarks(QVector <Landmark> landmarks);
    QVector <Landmark> getLandmarks();

    // TODO: Consider the gps as a point with uncertainty
    void setGPS(xyz gps);
    xyz getGPS();

    bool isGPSTooOld();
    bool isLandmarkTooOld();

    double getElapsedTime();

    std::string toString();
    void findYourself();
};

#include "hybrid.h"

#endif // ROBO_H
