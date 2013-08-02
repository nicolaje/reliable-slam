#include "besefastslam.h"
#include <ibex/ibex.h>
#include <eigen3/Eigen/Eigen>
#include <../../General/Utils/utils.h>
#include <../../FastSLAM/FastSLAM1_0/resampling.h>

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

void BESEFastSLAM::initParticles(Vector3d linearMotion, Vector3d angularMotion)
{
    Vector3d robotPosition,robotOrientation,robotLinearMotion,robotAngularMotion;
    robotPosition=Utils::intervalVectorToEigenVector(this->beseEstimator->getPosition());
    robotOrientation=Utils::intervalVectorToEigenVector(this->beseEstimator->getOrientation());
    robotLinearMotion=linearMotion; // = Utils::intervalVectorToEigenVector(this->beseEstimator->getLinearMotion());
    robotAngularMotion=angularMotion; // = Utils::intervalVectorToEigenVector(this->beseEstimator->getAngularMotion());

    for(int i=0; i<particleNb; i++){
        std::cout << "i : " << i << std::endl;
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
    // We could:
    // - put the midbox state in the particles
    // - put the measurements in the particles <- the one we use
    double depth=data[2].mid();
    Vector3d orient,linMotion,angMotion;
    std::vector<double> landmarksMeasurements;
    for(int i=0;i<3;i++){
        orient[i]=data[3+i].mid();
        linMotion[i]=data[6+i].mid();
        angMotion[i]=data[9+i].mid();
    }
    for(int j=0;j<this->beseEstimator->getLandmarkNB();j++)
        landmarksMeasurements.push_back(data[12+j].mid());
    updateRobotDepth(depth);
    updateRobotOrientation(orient);
    updateRobotMotion(linMotion,angMotion);
    reSample();
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
    this->particles=ReSampling::resamplingHybrid(this->particles,this->beseEstimator->getState());
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
        double d=positions[i][2];
        particles[i].updateRobotDepth(d);
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
    std::vector<Vector3d> linearMotions=FastSLAM::drawSamples(particleNb,linearMotion,Robot::SIGMA_FACTOR*this->linearMotionCovariance);
    std::vector<Vector3d> angularMotions=FastSLAM::drawSamples(particleNb,angularMotion,Robot::SIGMA_FACTOR*this->angularMotionCovariance);
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
}


bool BESEFastSLAM::isConsistent(IntervalVector iVector, VectorXd eVector)
{
    return iVector.is_superset(Utils::eigenVectorToIntervalVector(eVector));
}
