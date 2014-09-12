#include <QtGui/QApplication>
#include <QDebug>
#include "dados.h"
#include <iostream>
#include "robo.h"
#include <time.h>

#include <hybrid.h>

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
/*

//-----
    int i=0;
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

    cout<<robo.mLocalizationSystem->searchSpace<<endl;

    //chama todos
    //robo.mLocalizationSystem->contractByAllQIntersection();

    //chama um a um
    vector <Ctc*> contractors,aux1,aux2;
    contractors=robo.mLocalizationSystem->composeContractorByDepth();
    aux1=robo.mLocalizationSystem->composeContractorByDistance();
    aux2=robo.mLocalizationSystem->composeContractorByGPS();
    contractors.insert(contractors.begin(), aux1.begin(),aux1.end());
    contractors.insert(contractors.begin(),aux2.begin(),aux2.end());
    robo.mLocalizationSystem->contractUsingComposition(contractors);//com CtcQInter

    cout<<robo.mLocalizationSystem->searchSpace<<endl;
*/
 //-------------


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
