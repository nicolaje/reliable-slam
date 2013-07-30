#include <ibex/ibex.h>
#include <QDebug>
#include <bese.h>
#include <stdlib.h>
#include "../../General/Utils/morsedataparser.h"
#include "../../General/Utils/robot.h"

using namespace ibex;

int main(int argc, char *argv[])
{
    QFile *out=new QFile("../Results/BESE/DeadReckoning3.res");
    if(!out->open(QIODevice::WriteOnly)){
        qDebug() << "Failed to open output file";
        return 1;
    }
    QFile *groundTruth=new QFile("../Results/BESE/GroundTruth3.res");
    if(!groundTruth->open(QIODevice::WriteOnly)){
        qDebug() << "Failed to open ground truth file";
        return 1;
    }

    MORSEDataParser p("/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Simulations/data/4-150_150_30_25_long.log",1,4);
    IntervalVector initState(3+3+3*4);
    Robot r=p.nextRecord()[0];

    IntervalVector robot=r.asIntervalVector();
    for(int i=0;i<3; i++){
        initState[i]=robot[i];
        initState[3+i]=robot[3+i];
    }

    initState[6]=Interval(-64.84536338313981,-44.84536338313981);
    initState[7]=Interval(42.115060540584906,62.115060540584906);
    initState[8]=Interval(-36.18112690511693,-16.18112690511693);

    initState[9]=Interval(-46.739646139086744,-26.739646139086744);
    initState[10]=Interval(-1.6847369362088642,1.6847369362088642);
    initState[11]=Interval(-37.75254467605631,-17.75254467605631);

    initState[12]=Interval(12.738945908414436,32.738945908414436);
    initState[13]=Interval(33.30850267032697,53.30850267032697);
    initState[14]=Interval(-39.530702066128825,-19.530702066128825);

    initState[15]=Interval(-80.74787852169905,-60.74787852169905);
    initState[16]=Interval(40.36476558798046,60.36476558798046);
    initState[17]=Interval(-37.836164660474733,-17.836164660474733);

    BESE estimator(initState,1,4);

    estimator.updateData(r);
    Interval dt(0.1,0.11);

    int j=0;
    while(p.hasDataLeft()){
        j++;
        std::cout << j << std::endl;
        estimator.predict(dt);
        r=p.nextRecord()[0];
        estimator.updateData(r);
        IntervalVector p=r.positionAsIntervalVector();

        IntervalVector *obs=r.getObservationsAsIntervalVector();
        IntervalVector updObs(1+3+estimator.getLandmarkNB());
        updObs[0]=p[2]; // Pressure sensor
        for(int i=0; i<3; i++){
            updObs[1+i]=(*obs)[i];
        }
        for(int i=0; i<estimator.getLandmarkNB(); i++){
            updObs[1+3+i]=(*obs)[9+i];
        }

            out->write(estimator.toString().c_str());
            groundTruth->write(r.groundTruthToString().c_str());
            double *pos=r.getPosition();
            IntervalVector posV(3);
            for(int i=0;i<3;i++){
                posV[i]=pos[i];
            }
        estimator.update(&updObs);
    }
    std::cout << "Position: " << estimator.getPosition() << std::endl;
    out->close();
    groundTruth->close();
}
