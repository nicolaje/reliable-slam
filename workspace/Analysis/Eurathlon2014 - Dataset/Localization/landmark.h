#ifndef LANDMARK_H
#define LANDMARK_H
#include "configuracaoes.h"
//#include "interval.h"
#include "ibex.h"

using namespace ibex;

class Landmark
{
public:
    Landmark();
    xyz posicao;
    Interval dist;
    int id;
};

#endif // LANDMARK_H
