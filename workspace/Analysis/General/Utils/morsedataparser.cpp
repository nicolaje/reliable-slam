#include "morsedataparser.h"

MORSEDataParser::MORSEDataParser(QString data_file, int nbRobots, int nbLandmarks)
{
    file=new QFile(data_file);
    if(!file->open(QIODevice::ReadOnly)){
        qDebug() << "fail";
    }else{
        file->readLine(); // drop the 1st comment line

        nbRobots=nbRobots;
        nbLandmarks=nbLandmarks;

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
    double landmarks[nbLandmarks];

    double positionNoisy[3], orientationNoisy[3];
    double angularSpeedNoisy[3], linearSpeedNoisy[3];
    double accelerationNoisy[3];
    double landmarksNoisy[nbLandmarks];

    int width=2*(Robot::NB_COLUMNS+nbLandmarks);

    for(int i=0; i<nbRobots; i++){
        Robot r;
        for(int j=0; j<3; j++){
            position[j]=res.value(i*width+j).toDouble();
            orientation[j]=res.value(i*width+3+j).toDouble();
            angularSpeed[j]=res.value(i*width+6+j).toDouble();
            linearSpeed[j]=res.value(i*width+9+j).toDouble();
            acceleration[j]=res.value(i*width+12+j).toDouble();
        }
        for(int l=0; l<nbLandmarks; l++){
            landmarks[l]=res.value(i*width+Robot::NB_COLUMNS+l).toDouble();
            landmarksNoisy[l]=res.value(i*width+Robot::NB_COLUMNS*2+nbLandmarks+l).toDouble();
        }
        qDebug() << position[0] << position[1] << position[2];
        robots.push_back(r);
    }
    return robots;
}
