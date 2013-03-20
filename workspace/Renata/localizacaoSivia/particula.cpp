#include "particula.h"



//*********************************************************************
//******************       CONSTRUCTEURS         **********************
//*********************************************************************
particula::particula()
{
    pose pos;
    double peso;
    int sit;
    int id;

}

//----------------------------------------------------------------------
//box::~box () {delete [] data;}
//----------------------------------------------------------------------
//*********************************************************************
//******************    FUNCTIONS MEMBRES     *************************
//*********************************************************************
double particula::Distancia(vector<QGraphicsPolygonItem*> obstaculos, QGraphicsLineItem *l, particula p ){
    double distancia=-1;
    for(int h=0;h<obstaculos.size();h++){
        double aux;
        QGraphicsPolygonItem* obs=obstaculos[h];
        if(l->shape().intersects(obs->shape())){
            QPainterPath interseccao;
            interseccao=l->shape().intersected(obs->shape());
            for(int r=0;r<interseccao.elementCount();r++){
                QPointF pinters= QPointF(interseccao.elementAt(r).x,interseccao.elementAt(r).y);
                aux= sqrt(pow((p.pos.x-pinters.x()),2)+pow((p.pos.y-pinters.y()),2));
                if(distancia==-1 || aux<distancia)distancia=aux;
            }
        }
    }
    //qDebug()<<"dist"<<distancia;
    return distancia;

}


/*
double box::Width(void)
{   box X=*this;
    int i=AxePrincipal(X);
    interval Xi=X[i];
    double w=Xi.sup-Xi.inf;
    return (w);
}


box& box::Intersect(const box& Y)
{  box X=*this;
   box Z=Inter(X,Y);
   *this=Z;
}
*/



//*********************************************************************
//******************    FONCTION NON MEMBRES     **********************
//*********************************************************************
/*
void Update(box& X)
{ for (int i=1; i<=Size(X); i++)
  { if (X[i].isEmpty)
       { for (int j=1; j<=Size(X); j++)
             X[j]=interval(); return; }
   }
}

*/









