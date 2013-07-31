#include "positionloader.h"
#include <QFile>
#include <QDebug>
#include <QStringList>

using namespace Eigen;
using namespace ibex;

PositionLoader::PositionLoader(QString data_file)
{
    QFile *f=new QFile(data_file);
    if(!f->open(QIODevice::ReadOnly)){
        qDebug() << "Failed to open position file.";
    }else{
        // Load the data
        while(!f->atEnd()){
            QString line=f->readLine();
            QStringList splitted(line.split(";"));
            Vector3d v;
            v << splitted.value(0).toDouble(),splitted.value(1).toDouble(),splitted.value(2).toDouble();
            landmarks.push_back(v);
        }
    }
}

std::vector<Vector3d> PositionLoader::getLandmarksAsVector()
{
    return landmarks;
}


std::vector<IntervalVector> PositionLoader::getLandmarksAsIntervalVector(double errorX, double errorY, double errorZ)
{
    double e[3][2]={{-errorX,errorX},{-errorY,errorY},{-errorZ,errorZ}};
    IntervalVector error(3,e);
    std::vector<IntervalVector> res;
    for(int i=0;i<landmarks.size();i++){
        IntervalVector v(3);
        v[0]=landmarks[i][0];
        v[1]=landmarks[i][1];
        v[2]=landmarks[i][2];
        v+=error;
        res.push_back(v);
    }
    return res;
}

int PositionLoader::getLandmarksNB()
{
    return landmarks.size();
}
