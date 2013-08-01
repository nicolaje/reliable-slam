#include <QCoreApplication>
#include <iostream>
#include "../../General/Utils/morsedataparser.h"
#include "../../General/Utils/robot.h"
#include "../../General/Utils/positionloader.h"
#include "besefastslam.h"
#include <ibex/ibex.h>
#include <eigen3/Eigen/Eigen>
#include <vector>

using namespace ibex;
using namespace Eigen;

#define PARTICLE_NB 1000
#define LM_COV \
    5,0,0,\
    0,5,0,\
    0,0,5

////////////////////////////
//#######################//
//## SENSOR PARAMETERS #//
//#####################//
////////////////////////
#define POS_COV \
    2.5,0,0,\
    0,2.5,0,\
    0,0,0.15
#define OR_COV \
    pow(0.02*M_PI/180.,2),0,0,\
    0,pow(0.02*M_PI/180.,2),0,\
    0,0,pow(0.02*M_PI/180.,2)
#define LIN_COV \
    pow(0.04,2),0,0,\
    0,pow(0.04,2),0,\
    0,0,pow(0.04,2)
#define ANG_COV \
    pow(0.01*M_PI/180.,2),0,0,\
    0,pow(0.01*M_PI/180.,2),0,\
    0,0,pow(0.01*M_PI/180.,2)
#define PING_COV 0.3

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile *out=new QFile("../Results/DeadReckoning3.res");
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

    Matrix3d positionCovariance,orientationCovariance,linearMotionCovariance,angularMotionCovariance;
    positionCovariance << POS_COV;
    orientationCovariance << OR_COV;
    linearMotionCovariance << LIN_COV;
    angularMotionCovariance << ANG_COV;
    double pingerVariance=PING_COV;

    std::vector<Matrix3d> landmarksPosCovariances;
    Matrix3d c1,c2,c3,c4;
    c1 << LM_COV;
    c2 << LM_COV;
    c3 << LM_COV;
    c4 << LM_COV;
    landmarksPosCovariances.push_back(c1);
    landmarksPosCovariances.push_back(c2);
    landmarksPosCovariances.push_back(c3);
    landmarksPosCovariances.push_back(c4);

    BESEFastSLAM estimator(PARTICLE_NB,initState,1,pLoader.getLandmarksNB());
    estimator.setPositionCovariance(positionCovariance);
    estimator.setOrientationCovariance(orientationCovariance);
    estimator.setLinearMotionCovariance(linearMotionCovariance);
    estimator.setAngularMotionCovariance(angularMotionCovariance);
    estimator.setPingerCovariance(pingerVariance);

    Interval dt(0.1,0.11);

    int j=0;
    while(p.hasDataLeft()){
        j++;
        std::cout << j<<"th iteration"<<std::endl;
        estimator.predict(dt);
        r=p.nextRecord()[0];
        estimator.update(r.getObservationsAsIntervalVector());
    }

    return a.exec();
}
