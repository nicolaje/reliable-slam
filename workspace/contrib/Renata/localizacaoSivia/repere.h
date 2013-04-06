#ifndef REPERE_H
#define REPERE_H

#include <QObject>
#include <QtCore>
#include <QtGui>
#include "box.h"
#include "particula.h"


class repere : public QObject
{
    Q_OBJECT
public:
    QGraphicsScene* Scene;
    double xmin,xmax,ymin,ymax;

    explicit repere(QObject *parent = 0);
    repere(QObject *parent = 0,QGraphicsView* G=0,double xmin=0,double xmax=10,double ymin=0,double ymax=10);
    double xToPix(double x);
    double yToPix(double y);
    void DrawBox(interval X, interval Y, QPen pen1, QBrush brush1);
    void DrawEllipse(double cx, double cy, double r, QPen pen1, QBrush brush1);
    void DrawPolygone(double x,double y,double theta,vector<double> X, vector<double> Y, QPen pen1, QBrush brush1);
    void Save(QString nom);

    double pixToX(double x);
    double pixToY(double x);
    double ConvDistPixToCoor(double x);
    double ConvDistCoorToPix(double x);
    void desenhaLandmarks(vector<pose> landmarks);
    void Escreve(QString a);
    void Teste();
    void Desenha(double cx, double cy, double r, particula p, QPen pen1, QBrush brush1);
   /* void att();
    void att(QString nom, particula & real,particula & estimada, vector <box> & caixas,vector<QGraphicsPolygonItem*> & obstaculos);
*/




signals:

public slots:

};

#endif // REPERE_H
