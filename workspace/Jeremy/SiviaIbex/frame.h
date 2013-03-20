#ifndef FRAME_H
#define FRAME_H

#include <QObject>
#include <QtCore>
#include <QtGui>
#include <vector>
#include "ibex_IntervalVector.h"

using std::vector;
using ibex::Interval;

class Frame : public QObject {
    Q_OBJECT

public:
    QGraphicsScene* Scene;
    double xmin,xmax,ymin,ymax;

    explicit Frame(QObject *parent = 0);
    Frame(QObject *parent = 0,QGraphicsView* G=0,double xmin=0,double xmax=10,double ymin=0,double ymax=10);
    double xToPix(double x);
    double yToPix(double y);
    void DrawBox(Interval X, Interval Y, QPen pen1, QBrush brush1);
    void DrawEllipse(double cx, double cy, double r, QPen pen1, QBrush brush1);
    void DrawPolygone(double x,double y,double theta,vector<double> X, vector<double> Y, QPen pen1, QBrush brush1);
    void Save(QString nom);

signals:

public slots:

};

#endif // FRAME_H
