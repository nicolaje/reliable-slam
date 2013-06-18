#include "bese.h"
using namespace ibex;
BESE::BESE(ibex::IntervalVector initState, int nbRobots, int nbLandmarks)
{
    this->state=initState;
    this->nbLandmarks=nbLandmarks;
    this->nbRobots=nbRobots;
}

void BESE::predict(ibex::IntervalVector measurements)
{

}
