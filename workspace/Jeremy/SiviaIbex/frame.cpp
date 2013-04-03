#include "frame.h"
#include <QDebug>

using ibex::Interval;

Frame::Frame(QObject *parent) :
    QObject(parent)
{
}
//--------------------------------------------------------------------------------------------------
Frame::Frame(QObject *parent,QGraphicsView* G,double xmin1, double xmax1,double ymin1, double ymax1) :
    QObject(parent)
{    Scene=new QGraphicsScene(this);
     G->setScene(Scene);
     xmin=xmin1; xmax=xmax1; ymin=ymin1; ymax=ymax1;
     Scene->setSceneRect(0,0,G->geometry().width()-3,G->geometry().height()-3);
     DrawBox(Interval(xmin,xmax),Interval(ymin,ymax),QPen(Qt::red),QBrush(Qt::NoBrush));
}
//--------------------------------------------------------------------------------------------------
double Frame::xToPix(double x)
{   double echx = Scene->width()/(xmax-xmin);
    return (x-xmin)*echx;
}
//--------------------------------------------------------------------------------------------------
double Frame::yToPix(double y)
{
    double echy = Scene->height()/(ymax-ymin);
    return Scene->height()-(y-ymin)*echy;
}
//--------------------------------------------------------------------------------------------------
void Frame::DrawBox(Interval X, Interval Y, QPen pen1, QBrush brush1)
{       QPolygonF box1;
        box1 << QPointF(xToPix(X.lb()),yToPix(Y.lb()))<< QPointF(xToPix(X.ub()),yToPix(Y.lb()))
             << QPointF(xToPix(X.ub()),yToPix(Y.ub()))<< QPointF(xToPix(X.lb()),yToPix(Y.ub()));
        QGraphicsPolygonItem *P;
        P=Scene->addPolygon(box1,pen1,brush1);
 }

//--------------------------------------------------------------------------------------------------
void Frame::DrawEllipse(double cx, double cy, double r, QPen pen1, QBrush brush1)
{
     Scene->addEllipse(xToPix(cx-r),yToPix(cy+r),xToPix(cx+r)-xToPix(cx-r),yToPix(cy-r)-yToPix(cy+r),pen1,brush1);
}
//--------------------------------------------------------------------------------------------------
void Frame::DrawPolygone(double x,double y,double theta,vector<double> X, vector<double> Y, QPen pen1, QBrush brush1)
{       QPolygonF poly1;
        for (int k=0;k<X.size();k++)
        {
            double x1=x+cos(theta)*X[k]-sin(theta)*Y[k];
            double y1=y+sin(theta)*X[k]+cos(theta)*Y[k];
            poly1 << QPointF(xToPix(x1),yToPix(y1));
        }
        QGraphicsPolygonItem *P;
        P=Scene->addPolygon(poly1,pen1,brush1);
 }
//--------------------------------------------------------------------------------------------------
void Frame::Save(QString nom)
{
    QImage *image = new QImage(QSize(400,400),QImage::Format_ARGB32);
    image->fill(QColor(Qt::white).rgb());
    QPainter *pngPainter = new QPainter(image);
    pngPainter->setRenderHint(QPainter::Antialiasing);
    Scene->render(pngPainter);
    pngPainter->end();
    image->save(nom+".png","PNG",100);
}
//--------------------------------------------------------------------------------------------------

