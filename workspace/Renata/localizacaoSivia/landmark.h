#ifndef __LANDMARK__
#define __LANDMARK__

#include <cmath>
using namespace std;
#include <iostream>
#include <vector>
#include <math.h>
#include "interval.h"
#include "incluir.h"
#include <QtGui>


class landmark
{
public:
    pose pos;
    interval dist;

//---------------------CONSTRUCTEURS--------------------------------------------
landmark ();
//------------------------------------
//double Distancia(vector<QGraphicsPolygonItem*> obstaculos, QGraphicsLineItem *l, particula p);

};
#endif
