#ifndef LANDMARK_H
#define LANDMARK_H
#include "configuracaoes.h"
#include "ibex.h"

using namespace ibex;

class Landmark
{
public:
    Landmark();
    xyz posicao;
    xyz angle;
    Interval dist;
    int id;
    double time;
};

#endif // LANDMARK_H
