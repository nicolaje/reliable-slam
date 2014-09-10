#ifndef FILTROPARTICULAS_H
#define FILTROPARTICULAS_H

#include <QVector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include "configuracaoes.h"
#include "landmark.h"
#include "particula.h"
#include "dados.h"

class FiltroParticulas
{
public:
    FiltroParticulas();
    void executarFiltro(QVector <xyz> poseXYZ, QVector <xyz> yawPitchRoll,QVector <xyz> velXYZ,QVector <QVector<transponder> > transponders,QVector <Landmark> landmarksUsados, int idExec);
    void roleta( QVector <Particula> & populacao);
    void criarPopulacao(IntervalVector searchSpace, QVector <Particula> & populacao, xyz yawPitchRoll);
};

#endif // FILTROPARTICULAS_H
