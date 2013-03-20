#ifndef __PARTICULA__
#define __PARTICULA__

#include <cmath>
using namespace std;
#include <iostream>
#include <vector>
#include <math.h>
#include "interval.h"
#include <QtGui>

#include "incluir.h"

/*struct pose{
    double x;
    double y;
    double th;
};*/

class particula
{
public:
    pose pos;
    double peso;
    int sit;
    int id;

//---------------------CONSTRUCTEURS--------------------------------------------
particula ();
//------------------------------------
double Distancia(vector<QGraphicsPolygonItem*> obstaculos, QGraphicsLineItem *l, particula p);

/*friend void Cplus  (box&, box&, box&, int sens);
friend void Cmoins (box&, box&, box&, int sens);
friend void C_q_in (box&, int, vector<box>&);
friend void Cnorm(interval&R, box& X);
friend void Cdistance(interval& R, box& X, box& Y);
friend void CProdScalaire(interval& R, box& X, box& Y);
friend void COrtho(box& X, box& Y);
friend void CProd(box& Y, interval& a, box& X, int sens);

*/

};
#endif
