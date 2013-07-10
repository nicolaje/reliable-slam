#include "morsedataparser.h"

MORSEDataParser::MORSEDataParser(QString data_file, int nbRobots, int nbLandmarks)
{
    file=new QFile(data_file);
    if(!file->open(QIODevice::ReadOnly)){
        qDebug() << "fail";
    }else{
        file->readLine(); // drop the 1st comment line

        this->nbRobots=nbRobots;
        this->nbLandmarks=nbLandmarks;

    }
}

vector<Robot> MORSEDataParser::nextRecord()
{
    vector<Robot> robots;
    QString l=file->readLine();
    QStringList res(l.split(";"));
    double position[3], orientation[3];
    double angularSpeed[3], linearSpeed[3];
    double acceleration[3];
    vector<double> landmarks;

    double positionNoisy[3], orientationNoisy[3];
    double angularSpeedNoisy[3], linearSpeedNoisy[3];
    double accelerationNoisy[3];
    vector<double> landmarksNoisy;

    int width=2*(Robot::NB_COLUMNS+nbLandmarks);

    for(int i=0; i<nbRobots; i++){
        Robot r;
        for(int j=0; j<3; j++){
            position[j]=res.value(i*width+j).toDouble();
            orientation[j]=res.value(i*width+3+j).toDouble();
            angularSpeed[j]=res.value(i*width+6+j).toDouble();
            linearSpeed[j]=res.value(i*width+9+j).toDouble();
            acceleration[j]=res.value(i*width+12+j).toDouble();
            positionNoisy[j]=res.value(Robot::NB_COLUMNS+nbLandmarks+j).toDouble();
            orientationNoisy[j]=res.value(Robot::NB_COLUMNS+nbLandmarks+3+j).toDouble();
            angularSpeedNoisy[j]=res.value(Robot::NB_COLUMNS+nbLandmarks+6+j).toDouble();
            linearSpeedNoisy[j]=res.value(Robot::NB_COLUMNS+nbLandmarks+9+j).toDouble();
            accelerationNoisy[j]=res.value(Robot::NB_COLUMNS+nbLandmarks+12+j).toDouble();
        }
        for(int l=0; l<nbLandmarks; l++){
            landmarks.push_back(res.value(i*width+Robot::NB_COLUMNS+l).toDouble());
            landmarksNoisy.push_back(res.value(i*width+Robot::NB_COLUMNS*2+nbLandmarks+l).toDouble());
        }
        r.setPosition(position);
        r.setOrientation(orientation);
        r.setRotationSpeed(angularSpeed);
        r.setSpeed(linearSpeed);
        r.setAcceleration(acceleration);
        r.setLandmarksMeasurements(landmarks);

        r.setPositionNoisy(positionNoisy);
        r.setOrientationNoisy(orientationNoisy);
        r.setRotationSpeedNoisy(angularSpeedNoisy);
        r.setSpeedNoisy(linearSpeedNoisy);
        r.setAccelerationNoisy(accelerationNoisy);
        r.setLandmarksMeasurementsNoisy(landmarksNoisy);

        robots.push_back(r);
    }
    return robots;
}

bool MORSEDataParser::hasDataLeft()
{
    return !this->file->atEnd();
}
