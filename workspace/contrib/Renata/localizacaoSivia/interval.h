#ifndef __INTERVAL__
#define __INTERVAL__

#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "iboolean.h"
#include <cmath>
using namespace std;


#define oo 1/0.0 //definition de l'infini noté oo
/* #define cos 0
   #define sin 1
   #define sinc 2
   #define tan 3
   #define atan 4  */


double Arccossin(const double&,const double&);
double Arg      (const double&,const double&);
double Sign     (const double& x);
double Chi      (const double& a,const double& b,const double& c);


class borne   // used by q_in only
{
public:
    double val;
    int ouverture;
    borne ();
    borne (const double&, const int&);
    friend bool     operator<(const borne &x, const borne &y);
};

class interval
{
public:
    double inf;
    double sup;
    bool isEmpty;

public:
    //--------------------------------------------------------------------------
    //                           CONSTRUCTEURS
    //--------------------------------------------------------------------------
    interval ();
    interval (const double&);    // Pas const pour conversion double -> interval
    interval (const double&, const double&);
    interval (const interval&);
    interval& operator= (const interval&);
    interval& Intersect(const interval&);
    //--------------------------------------------------------------------------
    //                          OPERATEURS
    //--------------------------------------------------------------------------
    friend interval operator& (const interval&,const interval&);
    friend interval operator+ (const interval&,const interval&);
    friend interval operator- (const interval&);
    friend interval operator- (const interval&, const interval&);
    friend interval operator* (const double, const interval&);
    friend interval operator* (const interval&, const double);
    friend interval operator* (const interval&, const interval&);
    friend interval operator/ (const interval& ,const interval&);
    friend std::ostream& operator<< (std::ostream&, const interval&);

    //--------------------------------------------------------------------------
    //                 FONCTION  ET PROCEDURES AMIES
    //--------------------------------------------------------------------------
    friend interval  Abs        (const interval&);
    friend interval  Cos        (const interval&);
    friend double    Det        (double&,double&,double&,double&);
    friend interval  Det        (interval&, interval&, interval&, interval&);
    friend double    DistanceDirSegment(double& mx, double& my, double& theta, double& ax, double& ay, double& bx, double& by);
    friend double    DistanceDirSegments(double& mx, double& my, double& theta, vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by);
    friend double    DistanceDirCercles(double& mx, double& my, double& theta, vector<double> cx, vector<double> cy, vector<double> r);

    friend interval  Exp        (const interval&);
    friend interval  Inflate    (const interval&,double);
    friend interval  Inter      (const interval&,const interval&);
    friend interval  Inter      (vector<interval> x);
    friend interval  InterMin   (const interval&,const interval&,char);
    friend interval  Log        (const interval&);
    friend interval  Max        (const interval&,const interval&);
    friend double    Max        (vector<double>& x);
    friend interval  Min        (const interval&,const interval&);
    friend interval  Min        (const interval&,const interval&,const interval&);
    friend double    Min        (vector<double>& x);
    friend interval  Parabole   (const interval&, double, double, double);
    friend interval  Power      (const interval&,int);
    friend interval  Pow        (const interval&, int);
    friend interval  Pow        (const interval&, int, int);
    friend interval  PowRoot    (const interval&, int, int);
    friend interval  Sin        (const interval&);
    friend interval  Sqr        (const interval&);
    friend interval  Sqrt       (const interval&);
    friend interval  Step       (const interval&);

    friend interval  InvSqrt    (const interval&);
    friend interval  Union      (const interval&, const interval&);
    friend interval  Union      (vector<interval> x);
    friend interval  Tan        (const interval&);

    friend iboolean  In         (const interval&,const interval&);

    friend bool      Disjoint   (const interval&,const interval&);
    friend bool      In         (double,const interval&);
    friend bool      Subset     (const interval&,const interval&);
    friend bool      SubsetStrict(const interval& a,const interval& b);
    friend bool      Subset     (const interval&,const interval&,double);
    friend bool      OverLap    (const interval&,const interval&);

    friend void      Sucre      (interval&, const interval&);
    friend void      Inter1     (interval&, interval&,const interval&,const interval&, const interval&);

    friend double      Inf        (const interval&);
    friend double      Sup        (const interval&);
    friend double      Rand       (const interval&);
    friend double      Center     (const interval&);
    friend double      Eloignement(const interval&, const interval&);
    friend double      Marge      (const interval&, const interval&);
    friend double      AbsMax     (const interval&);
    friend double      Todouble     (const interval&);
    friend double      Width      (const interval&);
    friend double      Width2      (const interval&);
    //--------------------------------------------------------------------------
    //    PROCEDURES TRADUISANT LE C.S.P POUR (SIN, COS, PLUS, EXP, ...)
    //--------------------------------------------------------------------------
    //             Contrainte Spécifique
    friend void      Csame_sign(interval&, interval&);
    friend void      Cgeq(interval&, interval&);
    //            Contraintes Unaires
    friend void      Cinteger    (interval&);
    friend void      Cboolean    (interval&);

    //             Contraintes Binaires
    friend void      Csin    (interval&, interval&, int);
    friend void      Ccos    (interval&, interval&, int);
    friend void      Csinc   (interval&, interval&, int);
    friend void      Cexp    (interval&, interval&, int);
    friend void      Clog    (interval&, interval&, int);
    friend void      Ctan    (interval&, interval&, int);
    friend void      Catan   (interval&, interval&, int);
    friend void      Csqr    (interval&, interval&, int);
    friend void      Csqrt   (interval&, interval&, int);

    friend void      Cmoins  (interval&, interval&, int);
    friend void      Cegal   (interval&, interval&, int);
    friend void      Cegal   (interval&, interval&);
    friend void      Cabs    (interval&, interval&, int);
    friend void      Crect   (interval&, interval&, int);
    friend void      Cpower  (interval&, interval&, int, int);
    friend void      Ctriangle (interval&, interval&, int);
    friend void      Cramp   (interval&, interval&, int, double a=0);
    friend void      Cstep   (interval&, interval&, int, double a=0);
    friend void      Cheaviside (interval&, interval&, int, double a=0);
    friend void      Csign   (interval&, interval&, int, double a=0);
    //              Contraintes Ternaires
    friend void      Crect   (interval&, interval&, interval&, int);
    friend void      Cplus   (interval&, interval&, interval&, int);
    friend void      Cplus   (double&,   interval&, interval&, int);
    friend void      Cplus   (interval&, double&,   interval& ,int);
    friend void      Cmoins  (interval&, interval&, interval&, int);
    friend void      Cmoins  (double&,   interval&, interval&, int);
    friend void      Cmoins  (interval&, interval&, double& x, int);
    friend void      CNorm   (interval&,interval&,interval& );
    friend void      Cprod   (interval&, interval&, interval&, int);
    friend void      Cprod   (interval& , double& , interval& , int);
    friend void      Cdiv    (interval&, interval&, interval&, int);
    friend void      Cmin    (interval&, interval&, interval&, int);
    friend void      Cmin    (interval&, interval&, interval&, interval&, int);
    friend int       Cmin    (interval&, vector<interval>&, int);
    friend void      Cmax    (interval&, interval&, interval&, int);
    friend void      C_q_in  (interval& x, int, vector<interval>&);

    friend int      CAngle  (interval&,interval&,interval&,interval&,interval&,bool);
    friend void     Cchi    (interval&, interval&, interval&, interval&);
    friend int     CDistanceDirSegment(interval&,interval&,interval&, interval&, double&, double&, double&,double&, int);
    friend void     CDistanceDirSegments(interval&, interval&, interval&, interval&, vector<double>, vector<double>, vector<double>, vector<double>);
    friend void     CinSegments(interval&, interval&, vector<double>, vector<double>, vector<double>, vector<double>);
    friend void     CinSegmentsOrCircles(interval& mx, interval& my,  vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by, vector<double> cx, vector<double> cy, vector<double> r);
    friend void CLegOnWallsOrCircles(interval& dist, interval& px, interval& py, interval& theta, vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by, vector<double> cx, vector<double> cy, vector<double> r);


    friend void     CLegOnWalls(interval&, interval&, interval&, interval&, vector<double>, vector<double>, vector<double>, vector<double>);
    friend void CPatteCroiseAucunSegment(interval& dist, interval& px, interval& py, interval& theta, vector<double> ax, vector<double> ay, vector<double> bx, vector<double> by);





    //------- Procédure de réduction élémentaires sur les intervalles ----------
    friend void      Contract0       (char, interval&, interval&, int, int n=0);
    friend void      Contract0       (char, interval&, interval&, interval&, int);
    friend void      Contract0       (char, interval&, double&    , interval&, int); //Luc

    friend void      Contract0       (char, interval&);
    //--------------------------------------------------------------------------
    //
    friend void      IntButterfly    (interval&, interval, interval, interval&, interval, int);


};
#endif
