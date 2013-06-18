#ifndef BESE_H
#define BESE_H
#include <ibex.h>

/**
 * @brief The BESE (Bounded Error State Estimator) class estimates the state of a robot
 * and the position of several landmarks using constraints propagation.
 * For now we only work in 2D with only one robot.
 */
class BESE
{
public:
    BESE(ibex::IntervalVector initState, int nbRobots, int nbLandmarks);
    void predict(ibex::IntervalVector measurements);
    void update(ibex::IntervalVector measurements);
private:
    ibex::IntervalVector state;
    ibex::Function motionModel;
    ibex::Function measurementModel;
    int nbRobots;
    int nbLandmarks;
};

#endif // BESE_H
