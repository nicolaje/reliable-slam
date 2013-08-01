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

    PositionLoader pLoader("/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Simulations/data/4-150_150_30_25.pos");
    MORSEDataParser p("/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Simulations/data/4-150_150_30_25_spirals.log",1,pLoader.getLandmarksNB());

    std::vector<IntervalVector> initMap=pLoader.getLandmarksAsIntervalVector(30,30,10);

    IntervalVector initState(3+3+3*pLoader.getLandmarksNB());
    Robot r=p.nextRecord()[0];

    IntervalVector robot=r.asIntervalVector();
    for(int i=0;i<3; i++){
        initState[i]=robot[i];
        initState[3+i]=robot[3+i];
    }

    for(int i=0;i<pLoader.getLandmarksNB();i++){
        IntervalVector lPos=initMap[i];
        for(int j=0;j<3;j++){
            initState[6+3*i+j]=lPos[j];
        }
    }

    BESE estimator(initState,1,pLoader.getLandmarksNB());
    std::cout << "Init state: "<<initState<<std::endl;

    estimator.update(r.getObservationsAsIntervalVector());
    Interval dt(0.1,0.11);

    int j=0;
    while(p.hasDataLeft()){
        j++;
        std::cout << j << std::endl;
        estimator.predict(dt);
        r=p.nextRecord()[0];

        out->write(estimator.toString().c_str());
        groundTruth->write(r.groundTruthToString().c_str());

        estimator.update(r.getObservationsAsIntervalVector());
    }
    std::cout << "Position: " << estimator.getPosition() << std::endl;
    std::cout << "Map: " << estimator.getMap() << std::endl;
    out->close();
    groundTruth->close();
}
