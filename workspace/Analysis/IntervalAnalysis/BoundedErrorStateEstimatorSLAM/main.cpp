#include <ibex/ibex.h>
#include <QDebug>
#include <bese.h>
#include <stdlib.h>
#include "../../General/Utils/morsedataparser.h"
#include "../../General/Utils/robot.h"
#include "../../General/Utils/positionloader.h"

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
    PositionLoader pLoader("/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Simulations/data/4-150_150_30_25.pos");
    //TODO:: add a getLandmarksNB() method in positionloader

    std::vector<IntervalVector> initMap=pLoader.getLandmarksAsIntervalVector(10,10,10);

    IntervalVector initState(3+3+3*4);
    Robot r=p.nextRecord()[0];

    IntervalVector robot=r.asIntervalVector();
    for(int i=0;i<3; i++){
        initState[i]=robot[i];
        initState[3+i]=robot[3+i];
    }

    for(int i=0;i<initMap.size();i++){
        IntervalVector lPos=initMap[i];
        for(int j=0;j<3;j++){
            initState[6+j]=lPos[j];
        }
    }

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
