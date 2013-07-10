#ifndef BESE_H
#define BESE_H
#include <ibex.h>
#include <string>
#include <subpaving.h>
#include <../../General/Utils/robot.h>

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
    void predictByContractor(ibex::IntervalVector vector, ibex::Interval dt);
    void update(ibex::IntervalVector *vector);
    void updateData(Robot robot);

    ibex::IntervalVector getPosition();
    ibex::IntervalVector getOrientation();

    int getLandmarkNB();
    int getRobotNB();

    std::string toString();
    std::string debugToString();
private:
    /**
     * @brief state is a box containing the robot position and the map.
     */
    ibex::IntervalVector *state;

    /**
     * @brief measurements is a box containing sensors values
     */
    ibex::IntervalVector *measurements;

    ibex::Function* motionModel;

    ibex::Function* fPrime;

    ibex::Function* observationModel;

    ibex::Function* motionModelByContractor;
    ibex::CtcFwdBwd* motionContractor;
    ibex::CtcFixPoint* motionFixPointContractor;

    ibex::Function* sensorsModelByContractor;
    ibex::CtcFwdBwd* sensorsContractor;
    ibex::CtcFixPoint* sensorsFixPointContractor;

    ibex::Function makeObservationModel(ibex::IntervalVector obs);

    ibex::SubPaving stateAsSubPaving;
    int nbRobots;
    int nbLandmarks;
    bool useSubPavings;
};

#endif // BESE_H
