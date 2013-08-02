#include "besefastslam.h"
#include <ibex/ibex.h>
#include <eigen3/Eigen/Eigen>
#include <../../General/Utils/utils.h>

using namespace Eigen;
using namespace ibex;

BESEFastSLAM::BESEFastSLAM(int particleNb, ibex::IntervalVector initState, int nbRobots, int nbLandmarks)
{
    this->beseEstimator=new BESE(initState,nbRobots,nbLandmarks);
    this->particleNb=particleNb;
}

void BESEFastSLAM::setPositionCovariance(Eigen::Matrix3d positionCovariance)
{
    this->positionCovariance=positionCovariance;
}

void BESEFastSLAM::setOrientationCovariance(Eigen::Matrix3d orientationCovariance)
{
    this->orientationCovariance=orientationCovariance;
}

void BESEFastSLAM::setLinearMotionCovariance(Eigen::Matrix3d linearMotionCovariance)
{
    this->linearMotionCovariance=linearMotionCovariance;
}

void BESEFastSLAM::setAngularMotionCovariance(Eigen::Matrix3d angularMotionCovariance)
{
    this->angularMotionCovariance=angularMotionCovariance;
}

void BESEFastSLAM::setPingerCovariance(double pingerVariance)
{
    this->pingerVariance=pingerVariance;
}

void BESEFastSLAM::initParticles()
{
    Vector3d robotPosition,robotOrientation,robotLinearMotion,robotAngularMotion;

    robotPosition=Utils::intervalVectorToEigenVector(this->beseEstimator->getPosition());
    robotOrientation=Utils::intervalVectorToEigenVector(this->beseEstimator->getOrientation());
    robotLinearMotion=Utils::intervalVectorToEigenVector(this->beseEstimator->getLinearMotion());
    robotAngularMotion=Utils::intervalVectorToEigenVector(this->beseEstimator->getAngularMotion());


    for(int i=0; i<particleNb; i++){
        Particle p(robotPosition, robotOrientation, robotLinearMotion, robotAngularMotion);
        std::vector<KalmanFilter> initMap;
        for(uint j=0;j<beseEstimator->getLandmarkNB();j++){
            Vector3d pos=FastSLAM::drawSamples(1,beseEstimator->getLandmark(j))[0];
            Matrix3d posCov=Utils::boxToCovarianceMatrix(beseEstimator->getLandmark(j),3);
            KalmanFilter kf(pos, posCov, this->pingerVariance);
            initMap.push_back(kf);
        }
        p.setInitMap(initMap);
        particles.push_back(p);
    }
}

void BESEFastSLAM::predict(ibex::Interval dt)
{
    this->beseEstimator->predict(dt);
    for(int i=0;i<particleNb;i++){
        particles[i].predict(dt.mid());
    }
}

void BESEFastSLAM::update(ibex::IntervalVector data)
{
    this->beseEstimator->update(data);
}

void BESEFastSLAM::normalize()
{
    double sum=0;
    for(int i=0;i<particleNb;i++){
        sum+=particles[i].getWeight();
    }
    for(int i=0;i<particleNb;i++){
        particles[i].normalizeWeight(sum);
    }
}


void BESEFastSLAM::reSample()
{
    IntervalVector robotPosition=beseEstimator->getPosition();
    IntervalVector robotOrientation=beseEstimator->getOrientation();

    IntervalVector map=beseEstimator->getMap();


}

void BESEFastSLAM::updateRobotPosition(Vector3d position)
{
    std::vector<Vector3d> positions=FastSLAM::drawSamples(particleNb,position,positionCovariance);
    for(int i=0;i<particleNb;i++){
        particles[i].updateRobotPosition(positions[i]);
    }
}

void BESEFastSLAM::updateRobotDepth(double depth)
{
    Vector3d v3d;
    v3d<<0,0,depth;
    std::vector<Vector3d> positions=FastSLAM::drawSamples(particleNb,v3d,positionCovariance);
    for(int i=0;i<particleNb;i++){
        particles[i].updateRobotDepth(positions[i][3]);
    }
}

void BESEFastSLAM::updateRobotOrientation(Vector3d orientation)
{
    std::vector<Vector3d> orientations=FastSLAM::drawSamples(particleNb,orientation,orientationCovariance);
    for(int i=0;i<particleNb;i++){
        particles[i].updateRobotOrientation(orientations[i]);
    }
}

void BESEFastSLAM::updateRobotMotion(Vector3d linearMotion, Vector3d angularMotion)
{
    std::vector<Vector3d> linearMotions=FastSLAM::drawSamples(particleNb,linearMotion,SIGMA_FACTOR*this->linearMotionCovariance);
    std::vector<Vector3d> angularMotions=FastSLAM::drawSamples(particleNb,angularMotion,SIGMA_FACTOR*this->angularMotionCovariance);
    for(int i=0;i<particleNb;i++){
        particles[i].updateRobotLinearMotion(linearMotions[i]);
        particles[i].updateRobotOrientationMotion(angularMotions[i]);
    }
}

void BESEFastSLAM::updateMap(std::vector<double> landmarksMeasurements)
{
    for(int p=0;p<particleNb;p++){
        particles[p].updateAllKFs(landmarksMeasurements);
    }
    normalize();
    particles=reSample();
}


bool BESEFastSLAM::isConsistent(IntervalVector iVector, VectorXd eVector)
{
    return iVector.is_superset(Utils::eigenVectorToIntervalVector(eVector));
}
