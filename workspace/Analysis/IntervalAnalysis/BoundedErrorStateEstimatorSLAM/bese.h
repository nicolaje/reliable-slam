#ifndef BESE_H
#include <ibex/ibex.h>
#include <string>
#include <../../General/Utils/robot.h>
#define BESE_H

/**
 * @brief The BESE (Bounded Error State Estimator) class estimates the state of a robot
 * and the position of several landmarks using constraints propagation.
 * For now we only work in 2D with only one robot.
 */
class BESE
{
public:
    BESE(ibex::IntervalVector initState, int nbRobots, int nbLandmarks, bool useSubPavings=false);

    void predict(ibex::Interval dt);
    void update(ibex::IntervalVector vector);

    ibex::IntervalVector getPosition();
    ibex::IntervalVector getOrientation();

    ibex::IntervalVector getLinearMotion();
    ibex::IntervalVector getAngularMotion();

    ibex::IntervalVector getMap();

    ibex::IntervalVector getState();

    int getLandmarkNB();
    int getRobotNB();

    std::string toString();
    std::string debugToString();
private:
    /**
     * @brief state is a box containing the robot position, orientation and the map.
     */
    ibex::IntervalVector *state;

    /**
     * @brief measurements is a box containing sensors values
     */
    ibex::IntervalVector *measurements;

    ibex::Function* fPrime;

    ibex::Function* euler;

    ibex::SubPaving stateAsSubPaving;
    int nbRobots;
    int nbLandmarks;
    bool useSubPavings;
};

#endif // BESE_H
