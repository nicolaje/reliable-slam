#ifndef HIBRIDO_H
#define HIBRIDO_H
//#include "sivia.h"
#include "configuracaoes.h"
#include <time.h>
#include <ibex.h>
#include "particula.h"
#include "filtroParticulas.h"
//#include "paletacores.h"
#include <iostream>
#include "robo.h"

using namespace  std;
using namespace ibex;

class Hibrido
{
public:
    Robo *mRobot;
    IntervalVector ambienteInicial;
    IntervalVector searchSpace;

    FiltroParticulas particleFilter;
    QVector<Particula> population;

    Particula worstParticle, bestParticle, avgParticle;

    ofstream logBoxes, logParticles, logRealPosition;

    Hibrido(Robo *robot);
    ~Hibrido();

    void executarLocalizacaoHibridaContratores();
    void createParticles();
    void moveParticles();
    void moveCaixa();
    void contractByDistance();
    void discardParticlesOutsideBox();
    void resamplingParticles();
    void weighParticles();

    void statistics();
    void log();
};

#endif // HIBRIDO_H
