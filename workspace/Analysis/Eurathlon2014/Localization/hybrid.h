#ifndef HYBRID_H
#define HYBRID_H
#include <ibex.h>
#include <iostream>
#include "filtroParticulas.h"
#include "configuracaoes.h"
#include "robo.h"

using namespace  std;
using namespace ibex;

class Hybrid
{
public:
    Robo *mRobot;
    IntervalVector allSpace;
    IntervalVector searchSpace;

    FiltroParticulas particleFilter;
    QVector<Particula> population;
    vector <Ctc*> contractors;

    Particula worstParticle, bestParticle, avgParticle;

    ofstream logBoxes, logParticles, logRealPosition;

    Hybrid(Robo *robot);
    ~Hybrid();

    void findWhereIAm();

    void createParticles();

    void moveParticles();
    void moveCaixa();

    void contractAllQIntersection();
    void contractAll();

    void contractByDistance();
    void contractByDepth();
    void contractByGPS();
    void contractByAngleOfPinger();
    void contractBySonarLocalization();

    void discardParticlesOutsideBox();
    void weighParticles();
    void resamplingParticles();

    void statistics();
    void log();
};

#endif // HYBRID_H
