#include <QtGui/QApplication>
#include <QDebug>
#include "dados.h"
#include <iostream>
#include "robo.h"
#include <time.h>

using namespace std;


int main(int argc, char *argv[])
{
    srand(time(NULL));

    QVector <xyz> poseXYZ;
    QVector <xyz> yawPitchRoll;
    QVector <xyz> acelXYZ;
    QVector <xyz> velAng;
    QVector <xyz> velXYZ;
    QVector < QVector <Landmark> > landmarksUsados;

    Dados d;
    d.carregarArquivo(poseXYZ, yawPitchRoll, acelXYZ, velAng, velXYZ, landmarksUsados);

    Robo robo;
    clock_t time = 0;
    for(int i=0; i<poseXYZ.size();i++)
    {
        cout << "Iteration: " << i << endl;

        time += 0.1* CLOCKS_PER_SEC;

        robo.setTruePose(poseXYZ[i]);
        robo.setAccelerometer(acelXYZ[i]);
        robo.setLinearVelocity(velXYZ[i]);
        robo.setLandmarks(landmarksUsados[i]);
        robo.setDeep(poseXYZ[i].z);
        if (i % 400 == 0)
            robo.setGPS(poseXYZ[i]);
        robo.setGyroscope(velAng[i]);
        robo.setGyrocompass(yawPitchRoll[i]);
        robo.mCurrentTime = time;

        cout << "Starting hybrid method..." << endl;
        robo.findYourself();
        cout << "...Finished" << endl << endl;
    }

    return 0;

}
