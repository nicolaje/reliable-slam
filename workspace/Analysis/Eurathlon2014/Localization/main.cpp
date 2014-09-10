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

    QVector <double> time;
    QVector <xyz> realPosition;
    QVector <xyz> gyrocompass;
    QVector <xyz> gpsAUV;
    QVector <xyz> gyroscope;
    QVector <xyz> loch_doppler;
    QVector <xyz> accelerometer;
    QVector < QVector <Landmark> > landmarksUsados;

    Dados d;
    d.carregarArquivo(time,realPosition, gyrocompass,gpsAUV, gyroscope, loch_doppler, accelerometer, landmarksUsados);

    Robo robo;
    for(int i=0; i<realPosition.size();i++)
    {
        cout << "Iteration: " << i << endl;

        robo.mCurrentTime = time[i]*CLOCKS_PER_SEC;
        robo.setTruePose(realPosition[i]);
        robo.setAccelerometer(accelerometer[i]);
        robo.setLinearVelocity(loch_doppler[i]);
        robo.setLandmarks(landmarksUsados[i]);
        robo.setDeep(realPosition[i].z);
        if (i % 400 == 0)
            robo.setGPS(gpsAUV[i]);
        robo.setGyroscope(gyroscope[i]);
        robo.setGyrocompass(gyrocompass[i]);

        cout << robo.toString() << endl;
        cout << "Starting hybrid method..." << endl;
        robo.findYourself();
        cout << "...Finished" << endl << endl;
    }

    return 0;

}
