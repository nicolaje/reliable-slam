#include "repere.h"
#include <QDebug>


repere::repere(QObject *parent) :
    QObject(parent)
{
}
//--------------------------------------------------------------------------------------------------
repere::repere(QObject *parent,QGraphicsView* G,double xmin1, double xmax1,double ymin1, double ymax1) :
    QObject(parent)
{    Scene=new QGraphicsScene(this);
     G->setScene(Scene);
     xmin=xmin1; xmax=xmax1; ymin=ymin1; ymax=ymax1;
     Scene->setSceneRect(0,0,G->geometry().width()-3,G->geometry().height()-3);
     DrawBox(interval(xmin,xmax),interval(ymin,ymax),QPen(Qt::black),QBrush(Qt::NoBrush));
}
//--------------------------------------------------------------------------------------------------
double repere::xToPix(double x)
{   double echx = Scene->width()/(xmax-xmin);
    return (x-xmin)*echx;
}
//--------------------------------------------------------------------------------------------------
double repere::yToPix(double y)
{
    double echy = Scene->height()/(ymax-ymin);
    return Scene->height()-(y-ymin)*echy;
}
//--------------------------------------------------------------------------------------------------
void repere::DrawBox(interval X, interval Y, QPen pen1, QBrush brush1)
{       QPolygonF box1;
        box1 << QPointF(xToPix(X.inf),yToPix(Y.inf))<< QPointF(xToPix(X.sup),yToPix(Y.inf))
             << QPointF(xToPix(X.sup),yToPix(Y.sup))<< QPointF(xToPix(X.inf),yToPix(Y.sup));
        QGraphicsPolygonItem *P;
        P=Scene->addPolygon(box1,pen1,brush1);
 }

//--------------------------------------------------------------------------------------------------
void repere::DrawEllipse(double cx, double cy, double r, QPen pen1, QBrush brush1)
{
     Scene->addEllipse(xToPix(cx-r),yToPix(cy+r),xToPix(cx+r)-xToPix(cx-r),yToPix(cy-r)-yToPix(cy+r),pen1,brush1);
}
//--------------------------------------------------------------------------------------------------
void repere::DrawPolygone(double x,double y,double theta,vector<double> X, vector<double> Y, QPen pen1, QBrush brush1)
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
void repere::Save(QString nom)
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

double repere::pixToX(double x){
    double a=Scene->width()/(xmax-xmin);
    return x/a+xmin;
}
double repere::pixToY(double y){
    double a=Scene->height()/(xmax-xmin);
    return (-y+Scene->height())/a+ymin;
}

double repere::ConvDistPixToCoor(double x){
    double a=Scene->height()/(xmax-xmin);
    return x/a;
}
double repere::ConvDistCoorToPix(double x){
    double a=Scene->height()/(xmax-xmin);
    return x*a;
}

void repere::Escreve(QString a){
    Scene->addSimpleText(a);
}

void repere::desenhaLandmarks(vector<pose> landmarks){
    for(int i=0;i<landmarks.size();i++){
        QPolygonF L;
        double t=0.1;
        L << QPointF(xToPix(landmarks[i].x-t),yToPix(landmarks[i].y-t))<< QPointF(xToPix(landmarks[i].x+t),yToPix(landmarks[i].y-t))
          << QPointF(xToPix(landmarks[i].x+t),yToPix(landmarks[i].y+t))<< QPointF(xToPix(landmarks[i].x-t),yToPix(landmarks[i].y+t));
        Scene->addPolygon(L,QPen(Qt::darkGreen),QBrush(Qt::darkGreen));
    }
}

void repere::Desenha(double cx, double cy, double r, particula p, QPen pen1, QBrush brush1)
{
    double x1,x2,y1,y2,cx2,cy2;
    int maxDist=10;
    x1=maxDist*cos(0*M_PI/180);
    y1=maxDist*sin(0*M_PI/180);
    x2=((x1*cos(p.pos.th*M_PI/180))-(y1*sin(p.pos.th*M_PI/180)));
    y2=((x1*sin(p.pos.th*M_PI/180))+(y1*cos(p.pos.th*M_PI/180)));
    cx2=p.pos.x+x2;
    cy2=p.pos.y+y2;

     Scene->addEllipse((cx-r),(cy+r),(cx+r)-(cx-r),(cy-r)-(cy+r),pen1,brush1);
     //Scene->addLine(xToPix(cx),yToPix(cy),cx2,cy2,pen1);
}

void repere::Teste()
{

    QPolygonF box1;
    box1 << QPointF(50,50)<< QPointF(80,50)<< QPointF(80,60)<< QPointF(70,60)<< QPointF(70,70)<< QPointF(50,70);
    QGraphicsPolygonItem *P;
    P=Scene->addPolygon(box1,QPen(Qt::darkGray),QBrush(Qt::darkGray));


    QPolygonF box2;
    box2 << QPointF(20,20)<< QPointF(51,20)<< QPointF(51,51)<< QPointF(20,51);
    QGraphicsPolygonItem *P2;
    P2=Scene->addPolygon(box2,QPen(Qt::red),QBrush(Qt::red));

    //P->collidingItems()
    qDebug()<< P->collidesWithItem(P2);

    QPainterPath s,s2,s3;
    s= P->shape();
    s2=P2->shape();

    //Scene->addPath(s,QPen(Qt::magenta),QBrush(Qt::yellow));

    Scene->addText("o")->setPos(85,85);

    QGraphicsLineItem *l;
    l=Scene->addLine(90,65,70,65,QPen(Qt::red));
    s2=l->shape();

    qDebug()<< "intersects: "<<s.intersects(s2);
    //qDebug()<< "intersected: "<<s.intersected(s2);


    s3=s.intersected(s2);



    Scene->addLine(50,65,50,65,QPen(Qt::green));
    Scene->addLine(70,65,70,65,QPen(Qt::green));

    qDebug()<< "intersected2:"<<P->shape().intersected(l->shape()).elementAt(1)<<s3.elementAt(1);

    qDebug()<< "intersected a:"<<P->shape().intersected(l->shape());
    qDebug()<< "intersected b:"<<l->shape().intersected(P->shape());



    vector<QGraphicsPolygonItem*> obstaculos;
    obstaculos.push_back(P);
    obstaculos.push_back(P2);


 /* QImage *image = new QImage(QSize(400,400),QImage::Format_ARGB32);
    image->fill(QColor(Qt::white).rgb());
    QPainter *pngPainter = new QPainter(image);
    pngPainter->setRenderHint(QPainter::Antialiasing);
    Scene->render(pngPainter);
    pngPainter->end();
    image->setText();
    //image->save(nom+".png","PNG",100);
    */
}
/*
void repere::att(){

    QImage *image = new QImage(QSize(400,400),QImage::Format_ARGB32);
    image->fill(QColor(Qt::white).rgb());
    QPainter *pngPainter = new QPainter(image);
    pngPainter->setRenderHint(QPainter::Antialiasing);
    Scene->render(pngPainter);
    pngPainter->end();
    //image->save("paving.png","PNG",100);
}

void repere::att(QString nom, particula & real,particula & estimada, vector <box> & caixas,vector<QGraphicsPolygonItem*> & obstaculos ){

    QImage *image = new QImage(QSize(400,400),QImage::Format_ARGB32);
    image->fill(QColor(Qt::white).rgb());
    QPainter *pngPainter = new QPainter(image);
    pngPainter->setRenderHint(QPainter::Antialiasing);
    for (int i=0;i<caixas.size();i++){
        box b=caixas[i];
        DrawBox(b[1],b[2],QPen(Qt::darkGray),QBrush(Qt::darkGray));
    }

    DrawEllipse(pixToX(real.pos.x),pixToY(real.pos.y),0.1,QPen(Qt::yellow),QBrush(Qt::yellow));
    DrawEllipse(pixToX(estimada.pos.x),pixToY(estimada.pos.y),0.1,QPen(Qt::blue),QBrush(Qt::blue));

    Scene->render(pngPainter);
    pngPainter->end();
    image->save(nom+".png","PNG",100);
}

*/
