#include <QApplication>
#include <iostream>
#include "mainwindow.h"
#include <eigen3/Eigen/Eigen>
#include <QDebug>
#include <vector>
#include "../../General/Utils/morsedataparser.h"
#include "../../General/Utils/robot.h"
#include "particle.h"
#include "fastslam.h"
#define PARTICLES_NB 10
#define DT 0.1

/////////////////////////
//####################//
//## MAP PARAMETERS #//
//##################//
/////////////////////
#define LM1 18,-30,3
#define LM2 -7,12,17
#define LM3 0,20,5
#define LM4 -27,-20,10
#define C1 \
    10,0,0,\
    0,10,0,\
    0,0,10
#define C2 \
    10,0,0,\
    0,10,0,\
    0,0,10
#define C3 \
    10,0,0,\
    0,10,0,\
    0,0,10
#define C4 \
    10,0,0,\
    0,10,0,\
    0,0,10

////////////////////////////
//#######################//
//## SENSOR PARAMETERS #//
//#####################//
////////////////////////
#define POS_COV \
    2.5,0,0,\
    0,2.5,0,\
    0,0,0.15
#define OR_COV \
    0.02*M_PI/180,0,0,\
    0,0.02*M_PI/180,0,\
    0,0,0.02*M_PI/180
#define LIN_COV \
    0.04,0,0,\
    0,0.04,0,\
    0,0,0.04
#define ANG_COV \
    0.01*M_PI,0,0,\
    0,0.01*M_PI,0,\
    0,0,0.01*M_PI
#define PING_COV 0.03
using namespace Eigen;

int main(int argc, char *argv[])
{
    std::vector<Particle> particles;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    MORSEDataParser p("/home/jem/reliable-slam/workspace/Simulations/Scenarios/2D-4Transponders/2D-4Transponders-Circle.res",1,4);
    Robot r=p.nextRecord()[0];

    Matrix3d positionCovariance,orientationCovariance,linearMotionCovariance,angularMotionCovariance;
    positionCovariance << POS_COV;
    orientationCovariance << OR_COV;
    linearMotionCovariance << LIN_COV;
    angularMotionCovariance << ANG_COV;
    double pingerVariance=PING_COV;

    // 4 landmarks here
    //
    std::vector<Vector3d> landmarksEstimates;
    Vector3d l1,l2,l3,l4;
    l1 << LM1;
    l2 << LM2;
    l3 << LM3;
    l4 << LM4;
    landmarksEstimates.push_back(l1);
    landmarksEstimates.push_back(l2);
    landmarksEstimates.push_back(l3);
    landmarksEstimates.push_back(l4);

    std::vector<Matrix3d> landmarksPosCovariances;
    Matrix3d c1,c2,c3,c4;
    c1 << C1;
    c2 << C2;
    c3 << C3;
    c4 << C4;
    landmarksPosCovariances.push_back(c1);
    landmarksPosCovariances.push_back(c2);
    landmarksPosCovariances.push_back(c3);
    landmarksPosCovariances.push_back(c4);

    FastSLAM estimator(positionCovariance,orientationCovariance,linearMotionCovariance,angularMotionCovariance,pingerVariance);
    estimator.initParticles(PARTICLES_NB,r.positionAsVect(),r.orientationAsVect(),r.linearMotionAsVect(),r.angularMotionAsVect(),landmarksEstimates,landmarksPosCovariances);

    estimator.predict(DT);

    while(p.hasDataLeft()){
        r=p.nextRecord()[0];
        estimator.updateMap(r.getLandmarksMeasurementsNoisy());
        estimator.updateRobotMotion(r.linearMotionAsVect(),r.angularMotionAsVect());
        estimator.updateRobotState(r.orientationAsVect());
    }

    return a.exec();
}
