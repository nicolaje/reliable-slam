#include <QApplication>
#include <iostream>
#include "mainwindow.h"
#include <eigen3/Eigen/Eigen>
#include <QDebug>
#include <vector>
#include "../../General/Utils/morsedataparser.h"
#include "../../General/Utils/robot.h"
#include "particle.h"
#include "fastslam.h"
#define PARTICLES_NB 1
#define DT 0.1

/////////////////////////
//####################//
//## MAP PARAMETERS #//
//##################//
/////////////////////
#define LM1 18,-30,3
#define LM2 -7,12,17
#define LM3 0,20,5
#define LM4 -27,-20,10
#define C1 \
    1,0,0,\
    0,1,0,\
    0,0,1
#define C2 \
    1,0,0,\
    0,1,0,\
    0,0,1
#define C3 \
    1,0,0,\
    0,1,0,\
    0,0,1
#define C4 \
    1,0,0,\
    0,1,0,\
    0,0,1

////////////////////////////
//#######################//
//## SENSOR PARAMETERS #//
//#####################//
////////////////////////
#define POS_COV \
    2.5,0,0,\
    0,2.5,0,\
    0,0,pow(0.15,2)
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
#define PING_COV pow(0.03,2)

using namespace Eigen;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    MORSEDataParser p("/home/jem/reliable-slam/workspace/Simulations/Scenarios/2D-4Transponders/2D-4Transponders-Circle.res",1,4);
    Robot r=p.nextRecord()[0];

    QFile *out=new QFile("../Results/DeadReckoning3.res");
    if(!out->open(QIODevice::WriteOnly)){
        qDebug() << "Failed to open output file";
        return 1;
    }

    Matrix3d positionCovariance,orientationCovariance,linearMotionCovariance,angularMotionCovariance;
    positionCovariance << POS_COV;
    orientationCovariance << OR_COV;
    linearMotionCovariance << LIN_COV;
    angularMotionCovariance << ANG_COV;
    double pingerVariance=PING_COV;

    // 4 landmarks here

    std::vector<Vector3d> landmarksEstimates;
    Vector3d l1,l2,l3,l4;
    l1 << LM1;
    l2 << LM2;
    l3 << LM3;
    l4 << LM4;
    landmarksEstimates.push_back(l1);
    landmarksEstimates.push_back(l2);
    landmarksEstimates.push_back(l3);
    landmarksEstimates.push_back(l4);

    std::vector<Matrix3d> landmarksPosCovariances;
    Matrix3d c1,c2,c3,c4;
    c1 << C1;
    c2 << C2;
    c3 << C3;
    c4 << C4;
    landmarksPosCovariances.push_back(c1);
    landmarksPosCovariances.push_back(c2);
    landmarksPosCovariances.push_back(c3);
    landmarksPosCovariances.push_back(c4);

    std::cout << "Position covariance: "<< positionCovariance << std::endl;
    std::cout << "Orientation covariance: " << orientationCovariance << std::endl;
    std::cout << "Motion covariance: " << linearMotionCovariance << std::endl;
    std::cout << "Orientation Speed covariance: " << angularMotionCovariance << std::endl;


    FastSLAM estimator(positionCovariance,orientationCovariance,linearMotionCovariance,angularMotionCovariance,pingerVariance);
    estimator.initParticles(PARTICLES_NB,r.positiontionTrueAsVect(),r.orientationTrueAsVect(),r.linearMotionTrueAsVect(),r.angularMotionTrueAsVect(),landmarksEstimates,landmarksPosCovariances);

    while(p.hasDataLeft()){
        estimator.updateMap(r.getLandmarksMeasurementsNoisy());
        estimator.updateRobotMotion(r.linearMotionTrueAsVect(),r.angularMotionTrueAsVect());
        estimator.updateRobotOrientation(r.orientationTrueAsVect());
        estimator.predict(DT);
        r=p.nextRecord()[0];
        std::ostringstream posTrue,posNoisy,posEst;
        posTrue << r.positionTrueAsVect()[0]<<";"<<r.positionTrueAsVect()[1]<<";"<<r.positionTrueAsVect()[2]<<";";
        posNoisy << r.positionAsVect()[0]<<";"<<r.positionAsVect()[1]<<";"<<r.positionAsVect()[2]<<";";
        posEst << estimator.getBestParticle().getPosition()[0]<<";"<<estimator.getBestParticle().getPosition()[1]<<";"<<estimator.getBestParticle().getPosition()[0]<<";";
        out->write(posTrue.str().c_str());
//        out->write(posNoisy.str().c_str());
        out->write(posEst.str().c_str());
        for(int i=0;i<4;i++){
            Vector3d lmV=estimator.getBestParticle().getMap()[i];
            std::ostringstream lm;
            lm << lmV[0]<<";"<<lmV[1]<<";"<<lmV[2]<<";";
            out->write(lm.str().c_str());
        }
        out->write("\n");
    }

    std::vector<Vector3d> map=estimator.getBestParticle().getMap();
    for(int i=0;i<map.size();i++){
        std::cout << i <<" : "<< map[i] <<std::endl;
    }
    out->close();
    return a.exec();
}
