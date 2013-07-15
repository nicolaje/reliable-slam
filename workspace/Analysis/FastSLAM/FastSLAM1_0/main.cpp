#include <QApplication>
#include <iostream>
#include "mainwindow.h"
#include <eigen3/Eigen/Eigen>
#include <QDebug>
#include <vector>
#include "../../General/Utils/morsedataparser.h"
#include "../../General/Utils/robot.h"
#include "particle.h"

int main(int argc, char *argv[])
{
    std::vector<Particle> particles;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    MORSEDataParser p("/home/jem/reliable-slam/workspace/Simulations/Scenarios/2D-4Transponders/2D-4Transponders-Circle.res",1,4);
    Robot r=p.nextRecord()[0];

    return a.exec();
}
