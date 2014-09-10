#include <QtGui/QApplication>
#include <QDebug>
#include "dados.h"
#include "configuracaoes.h"
#include "particula.h"
#include <time.h>
#include <stdlib.h>
#include "filtroParticulas.h"

#include "hibrido.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;



std::string stringalizar(double x)
{
    std::ostringstream oss;
    oss << x;
    return oss.str();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
        robo.setSensors(acelXYZ[i],velXYZ[i],landmarksUsados[i],20,poseXYZ[i],velAng[i],yawPitchRoll[i]);
        //cout << robo.toString() << endl;

        cout << "Starting hybrid method..." << endl;
        robo.findYourself();
        cout << "...Finished" << endl << endl;
//        if (i ==300)
//        {
////            cout << velXYZ[i].x << " " << velXYZ[i].y << " " << velXYZ[i].z << endl;
//            break;
//        }
    }

    return 0;

}
