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

    FastSLAM estimator;

    return a.exec();
}
