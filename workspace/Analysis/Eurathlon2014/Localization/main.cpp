#include <QtGui/QApplication>
#include <QDebug>
#include "dados.h"
#include <iostream>
#include "robo.h"

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
    for(int i=0; i<poseXYZ.size();i++)
    {
        cout << "Iteration: " << i << endl;

        robo.setSensors(acelXYZ[i],velXYZ[i],landmarksUsados[i],-20.,poseXYZ[i],velAng[i],yawPitchRoll[i]);

        cout << "Starting hybrid method..." << endl;
        robo.findYourself();
        cout << "...Finished" << endl << endl;
    }

    return 0;

}
