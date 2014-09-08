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

    double tempo(clock_t inicio);
    std::string stringalizar(double x);


    void carregarArquivo(QVector <xyz> & poseXYZ,
                         QVector <xyz> & yawPitchRoll,
                         QVector <xyz> & acelXYZ,
                         QVector <xyz> & velAng,
                         QVector <xyz> & velXYZ,
                         QVector < QVector <transponder> > & transponders);

    void carregarArquivo(QVector <xyz> & poseXYZ,
                                      QVector <xyz> & yawPitchRoll,
                                      QVector <xyz> & acelXYZ,
                                      QVector <xyz> & velAng,
                                      QVector <xyz> & velXYZ,
                                      QVector < QVector <Landmark> > & landmarks);

    void localizacaoLandmarks(QVector <Landmark> & localizacao);


};

#endif // DADOS_H
