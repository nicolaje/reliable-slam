#ifndef PARTICULA_H
#define PARTICULA_H
#include <math.h>
#include <stdlib.h>
#include "configuracaoes.h"
#include <QDebug>
#include "landmark.h"
//#include "interval.h"
//#include "box.h"
//using namespace std;

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
    void sample_motion_model_velocity(double v, double w, double x, double y, double th);
    double calcularPeso(QVector<transponder> transpVistos ,QVector<Landmark> localizacaoLandmarks);
    double calcularPeso(QVector<Landmark> localizacaoLandmarks);
    //int noConjunto(QVector <box> caixas);
    //void modeloMovimento(double vx, double vy, double vz, double wx, double wy, double wz);//com velocidade angular
    //int naCaixa(double xi, double xs, double yi, double ys, double zi, double zs);
    void modeloMovimento2(double vx, double vy, double vz, double phi, double theta, double psi, double mvAngx, double mvAngy, double mvAngz);//com angulos euler





};

#endif // PARTICULA_H
