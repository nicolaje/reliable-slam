#include "dados.h"
#include <QDebug>
#include "configuracaoes.h"
#include <QStringList>




Dados::Dados()
{

}

std::string Dados::stringalizar(double x)
{
    std::ostringstream oss;
    oss << x;
    return oss.str();
}

void Dados::carregarArquivo(
        QVector <double> &datasetTime,
        QVector <xyz> &realPosition,
        QVector <xyz> &gyrocompass,
        QVector <xyz> &gpsAUV,
        QVector <xyz> &gyroscope,
        QVector <xyz> &loch_doppler,
        QVector <xyz> &accelerometer,
        QVector < QVector <Landmark> > &landmarks){

    QString dataset=DATASET;
    QFile file(dataset);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug()<<"Problema: não abriu o "<<dataset;


    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        line=line.trimmed();
        QStringList list =line.split(";");

        if(!QString(list[0]).contains("#")){//se não forem linhas comentada
            int count=0;
            double time;
            xyz pose,euler, gpsSubmarine, vAng, vLin, acel;

            time=list[count].toDouble();count++;

            pose.x=list[count].toDouble();count++;
            pose.y=list[count].toDouble();count++;
            pose.z=list[count].toDouble();count++;

            euler.x=list[count].toDouble();count++;
            euler.y=list[count].toDouble();count++;
            euler.z=list[count].toDouble();count++;

            gpsSubmarine.x=list[count].toDouble();count++;
            gpsSubmarine.y=list[count].toDouble();count++;
            gpsSubmarine.z=list[count].toDouble();count++;

            vAng.x=list[count].toDouble();count++;
            vAng.y=list[count].toDouble();count++;
            vAng.z=list[count].toDouble();count++;

            vLin.x=list[count].toDouble();count++;
            vLin.y=list[count].toDouble();count++;
            vLin.z=list[count].toDouble();count++;

            acel.x=list[count].toDouble();count++;
            acel.y=list[count].toDouble();count++;
            acel.z=list[count].toDouble();count++;

            QVector <Landmark> lands;
            for(int i=0;i<NRO_TRANSPONDERS;i++){
                Landmark landmark;

                landmark.posicao.x=list[count].toDouble();count++;
                landmark.posicao.y=list[count].toDouble();count++;
                landmark.posicao.z=list[count].toDouble();count++;

                landmark.angle.x=list[count].toDouble();count++;
                landmark.angle.y=list[count].toDouble();count++;
                landmark.angle.z=list[count].toDouble();count++;

                double dist = list[count].toDouble();count++;
                landmark.dist=Interval(dist-(STD_DIST_TRANSP*SIGMA_FACTOR_TRA),dist+(STD_DIST_TRANSP*SIGMA_FACTOR_TRA));
                lands.push_back(landmark);
            }



            pose.xNoise=list[count].toDouble();count++;
            pose.yNoise=list[count].toDouble();count++;
            pose.zNoise=list[count].toDouble();count++;

            euler.xNoise=list[count].toDouble();count++;
            euler.yNoise=list[count].toDouble();count++;
            euler.zNoise=list[count].toDouble();count++;

            gpsSubmarine.xNoise=list[count].toDouble();count++;
            gpsSubmarine.yNoise=list[count].toDouble();count++;
            gpsSubmarine.zNoise=list[count].toDouble();count++;

            vAng.xNoise=list[count].toDouble();count++;
            vAng.yNoise=list[count].toDouble();count++;
            vAng.zNoise=list[count].toDouble();count++;

            vLin.xNoise=list[count].toDouble();count++;
            vLin.yNoise=list[count].toDouble();count++;
            vLin.zNoise=list[count].toDouble();count++;

            acel.xNoise=list[count].toDouble();count++;
            acel.yNoise=list[count].toDouble();count++;
            acel.zNoise=list[count].toDouble();count++;



            for(int i=0;i<lands.size();i++){

                lands[i].posicao.xNoise=list[count].toDouble();count++;
                lands[i].posicao.yNoise=list[count].toDouble();count++;
                lands[i].posicao.zNoise=list[count].toDouble();count++;

                lands[i].angle.xNoise=list[count].toDouble();count++;
                lands[i].angle.yNoise=list[count].toDouble();count++;
                lands[i].angle.zNoise=list[count].toDouble();count++;

                double dist = list[count].toDouble();count++;
                //lands[i].dist=Interval(dist-(STD_DIST_TRANSP*SIGMA_FACTOR_TRA),dist+(STD_DIST_TRANSP*SIGMA_FACTOR_TRA));
            }

            datasetTime.push_back(time);
            realPosition.push_back(pose);
            gyrocompass.push_back(euler);
            gpsAUV.push_back(gpsSubmarine);
            gyroscope.push_back(vAng);
            loch_doppler.push_back(vLin);
            accelerometer.push_back(acel);

            landmarks.push_back(lands);


        }
    }
}
