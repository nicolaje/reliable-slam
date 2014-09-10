#ifndef DADOS_H
#define DADOS_H
#include <QVector>
#include <QFile>
//#include "interval.h"
#include "configuracaoes.h"
#include "landmark.h"
#include <time.h>

class Dados
{
public:
    Dados();

    static std::string stringalizar(double x);

    void carregarArquivo(
            QVector <double> &datasetTime,
            QVector <xyz> &realPosition,
            QVector <xyz> &gyrocompass,
            QVector <xyz> &gpsAUV,
            QVector <xyz> &gyroscope,
            QVector <xyz> &loch_doppler,
            QVector <xyz> &accelerometer,
            QVector < QVector <Landmark> > &landmarks);

    void localizacaoLandmarks(QVector <Landmark> & localizacao);


};

#endif // DADOS_H
