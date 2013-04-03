#ifndef SOLVE_H
#define SOLVE_H

#include "ibex.h"

using namespace ibex;
using namespace std;

class Solve
{
public:
    Solve();
    static Ctc& getOutside();
    static Ctc& getInside();
};

#endif // SOLVE_H
