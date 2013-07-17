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
    positionCovariance
            << 2.5,0,0,
            0,2.5,0,
            0,0,0.15;
    orientationCovariance
            << 0.02*M_PI/180,0,0,
            0,0.02*M_PI/180,0,
            0,0,0.02*M_PI/180;
    linearMotionCovariance
            << 0.04,0,0,
            0,0.04,0,
            0,0,0.04;
    angularMotionCovariance
            << 0.01*M_PI,0,0,
            0,0.01*M_PI,0,
            0,0,0.01*M_PI;
    double pingerVariance=0.03;

    // 4 landmarks here
    //
    std::vector<Vector3d> landmarksEstimates;
    Vector3d l1,l2,l3,l4;
    l1 << 18,-30,3;
    l2 << -7,12,17;
    l3 << 0,20,5;
    l4 << -27,-20,10;
    landmarksEstimates.push_back(l1);
    landmarksEstimates.push_back(l2);
    landmarksEstimates.push_back(l3);
    landmarksEstimates.push_back(l4);

    std::vector<Matrix3d> landmarksCovariances;
    Matrix3d c1,c2,c3,c4;
    c1
            <<10,0,0,
            0,10,0,
            0,0,10;
    c2
            <<10,0,0,
            0,10,0,
            0,0,10;
    c3
            <<10,0,0,
            0,10,0,
            0,0,10;
    c4
            <<10,0,0,
            0,10,0,
            0,0,10;
    landmarksCovariances.push_back(c1);
    landmarksCovariances.push_back(c2);
    landmarksCovariances.push_back(c3);
    landmarksCovariances.push_back(c4);

    FastSLAM estimator(positionCovariance,orientationCovariance,linearMotionCovariance,angularMotionCovariance,pingerVariance);
    estimator.initParticles(PARTICLES_NB,r.positionAsVect(),r.orientationAsVect(),r.linearMotionAsVect(),r.angularMotionAsVect(),landmarksEstimates,landmarksCovariances);
//    Vector3d position,orientation,linearMotion,angularMotion;
//    estimator.initParticles(PARTICLES_NB);
//    estimator.initParticles(PARTICLES_NB,position,orientation,linearMotion,angularMotion,landmarksEstimates,landmarksCovariances);

    return a.exec();
}
