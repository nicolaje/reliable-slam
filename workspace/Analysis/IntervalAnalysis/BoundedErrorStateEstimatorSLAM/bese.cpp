#include "bese.h"
using namespace ibex;
BESE::BESE(IntervalVector initState, int nbRobots, int nbLandmarks, bool useSubPavings)
{
    *this->state=initState;
    this->nbLandmarks=nbLandmarks;
    this->nbRobots=nbRobots;
    this->useSubPavings=useSubPavings;
}

void BESE::predict(IntervalVector measurements, ibex::Interval dt)
{

}
