#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "morsedataparser.h"
#include "robot.h"

int main(int argc, char *argv[])
{
    MORSEDataParser parser("/home/jem/reliable-slam/workspace/Simulations/Scenarios/2D-4Transponders/2D-4Transponders-Circle2.res",1,4);

    vector<Robot> robots=parser.nextRecord();

    robots[0].toString();

    int i=0;
    for(i=0; i<10; i++){
        parser.nextRecord()[0].toString();
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
