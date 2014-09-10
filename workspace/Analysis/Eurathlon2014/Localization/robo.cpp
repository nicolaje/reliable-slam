#include "robo.h"
#include "dados.h"

Robo::Robo(): mLastEstimation(NULL)
{
    mLocalizationSystem = new Hibrido(this);
    curTime = -1;
}

Robo::~Robo()
{
    cout << "Deleting robot" << endl;
    delete mLocalizationSystem;
}

void Robo::setAccelerometer(xyz accelerometer)
{
    this->mLinearAcceleration.push_back(accelerometer);
}

xyz Robo::getAccelerometer() //aceleração linear 3 float
{

    return this->mLinearAcceleration[curTime];

}

void Robo::setLinearVelocity(xyz linearVelocity)
{
    this->mLinearVelocity.push_back(linearVelocity);
}

xyz Robo::getLinearVelocity()
{
    return this->mLinearVelocity[curTime];
}

void Robo::setLandmarks(QVector <Landmark> landmarks)
{
    this->mLandmarks.push_back(landmarks);
}

QVector <Landmark> Robo::getLandmarks()
{//gps+distance

    return this->mLandmarks[curTime];
}

void Robo::setDeep(double deep)
{
    this->mDeep.push_back(deep);
}

double Robo::getDeep()
{
    return this->mDeep[curTime];
}

void Robo::setGPS(xyz gps)
{
    this->mGPS.push_back(gps);
}

QVector<double> Robo::getGPS(){ //3 double
    QVector <double> gps;

    gps.push_back(this->mGPS[curTime].xNoise);
    gps.push_back(this->mGPS[curTime].yNoise);
    gps.push_back(this->mGPS[curTime].zNoise);
    gps.push_back(0.1);

    return gps;// aceleração x, y, z e tempo
}

void Robo::setGyroscope(xyz gyroscope)
{
    this->mAngularVelocity.push_back(gyroscope);
}

xyz Robo::getGyroscope() //velocidade angular 3 float da 7 a 9 primeira 0 =6 7 8
{
    return this->mAngularVelocity[curTime];
}

void Robo::setGyrocompass(xyz gyrocompass)
{
    this->mGyrocompass.push_back(gyrocompass);
}

xyz Robo::getGyrocompass() //angulos 3 float
{
    //euler
    return this->mGyrocompass[curTime];
}

xyz Robo::getDeltaHeading()
{
    xyz ret;

    if (curTime > 0)
    {
        ret.x = this->mGyrocompass[curTime].x - this->mGyrocompass[curTime-1].x;
        ret.y = this->mGyrocompass[curTime].y - this->mGyrocompass[curTime-1].y;
        ret.z = this->mGyrocompass[curTime].z - this->mGyrocompass[curTime-1].z;
    }

    return ret;
}

/*
getCamera(){//3 imagens

}

*/

double Robo::getElapsedTime()
{
    double elapsedTime = 0.;

    if (mLastEstimation != NULL)
        elapsedTime = double(mCurrentTime - mLastEstimation) / CLOCKS_PER_SEC;

    return 0.1; //elapsedTime;
}

void Robo::setSensors(xyz accelerometer,xyz linearVelocity,QVector <Landmark> landmarks, double deep,xyz gps,xyz gyroscope,xyz gyrocompass)
{
    this->setAccelerometer(accelerometer);
    this->setLinearVelocity(linearVelocity);
    this->setLandmarks(landmarks);
    this->setDeep(deep);
    this->setGPS(gps);
    this->setGyroscope(gyroscope);
    this->setGyrocompass(gyrocompass);

    curTime += 1;
}

std::string Robo::toString()
{
    std::ostringstream oss;

    xyz accelerometer = this->getAccelerometer();
    QVector<double> gps = this->getGPS();
    xyz gyrocompass = this->getGyrocompass();
    xyz gyroscope = this->getGyroscope();
    xyz linearVelocity = this->getLinearVelocity();

    oss
            << accelerometer.x  << accelerometer.y  << accelerometer.z
            << gps[0]           << gps[1]           << gps[2]           << gps[3]
            << gyrocompass.x    << gyrocompass.y    << gyrocompass.z
            << gyroscope.x      << gyroscope.y      << gyroscope.z
            << linearVelocity.x << linearVelocity.y << linearVelocity.z
            << this->getDeep();

    return oss.str();

}

void Robo::findYourself()
{
    mCurrentTime = clock();
    mLocalizationSystem->executarLocalizacaoHibridaContratores();
    mLastEstimation = mCurrentTime;
}
