#ifndef PARTICULA_H
#define PARTICULA_H
#include <math.h>
#include <stdlib.h>
#include "configuracaoes.h"
#include <QDebug>
#include <ibex.h>
#include "landmark.h"
//#include "interval.h"
//#include "box.h"
//using namespace std;
using namespace ibex;

class Particula
{
public:
    Particula();
    int id;
    double peso;
    xyz pose;
    xyz yawPitchRoll;

//    acho que não precisa....
//    xyz aceleracaoXYZ;
//    xyz velAngular;
//    xyz velXYZ;

    double sample_normal_distribution(double b);
    double fRand(double fMin, double fMax);
    double fRandCentred(double middle, double error);
    double fRand(Interval interval);
    void sample_motion_model_velocity(double v, double w, double x, double y, double th);
    double calcularPeso(QVector<transponder> transpVistos ,QVector<Landmark> localizacaoLandmarks);
    double calcularPeso(QVector<Landmark> localizacaoLandmarks);
    //int noConjunto(QVector <box> caixas);
    //void modeloMovimento(double vx, double vy, double vz, double wx, double wy, double wz);//com velocidade angular
    //int naCaixa(double xi, double xs, double yi, double ys, double zi, double zs);
    void modeloMovimento2(double vx, double vy, double vz, double mvAngx, double mvAngy, double mvAngz, double elapsedTime);//com angulos euler





};

#endif // PARTICULA_H
