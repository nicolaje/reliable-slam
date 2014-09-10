#include "particula.h"

Particula::Particula()
{
}

//valor aleatorio entre fMin e fMax
double Particula::fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

double Particula::fRandCentred(double middle, double error)
{
    return this->fRand(middle - error,middle + error);
}

double Particula::fRand(Interval interval)
{
    return this->fRand(interval.ub(),interval.lb());
}

//valor aleatorio de distribuicao normal
double Particula::sample_normal_distribution(double b){
    double r=0;
    for(int i=0;i<12;i++){
        r=r+fRand(-1,1);
    }
    return (b/6)*r;
}

double Particula::calcularPeso(QVector<Landmark> localizacaoLandmarks)
{
    double desvio=DESVIO_PADRAO_PESO_PARTICULAS;

    this->peso=1;

    for(int i=0;i<localizacaoLandmarks.size();i++)
    {
        //distancia entre a partícula e o transponder
        double d=sqrt(pow(this->pose.x-localizacaoLandmarks[i].posicao.x,2)+pow(this->pose.y-localizacaoLandmarks[i].posicao.y,2)+pow(this->pose.z-localizacaoLandmarks[i].posicao.z,2));

        double gaussiana=(1/sqrt(2*M_PI*pow(desvio,2)))*(exp(-(pow(d-localizacaoLandmarks[i].dist.mid(),2)/(2*pow(desvio,2)))));
        this->peso= this->peso*gaussiana;//valor da gaussiana que representa a distancia do transponder

    }

    return this->peso;
}


void Particula::modeloMovimento2(double vx, double vy, double vz, double mvAngx, double mvAngy, double mvAngz, double elapsedTime){
    //USA ANGULOS DE EULER (PHI THETA PSI)

    double phi, theta, psi;
    phi=this->yawPitchRoll.x+mvAngx;
    theta=this->yawPitchRoll.y+mvAngy;
    psi=this->yawPitchRoll.z+mvAngz;


    double erroVX=sample_normal_distribution(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER);
    double erroVY=sample_normal_distribution(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER);
    double erroVZ=sample_normal_distribution(SIGMA_FACTOR_VEL*STD_VEL_DOPPLER);
    double erroPHI=sample_normal_distribution(SIGMA_FACTOR_ORI*STD_ORIENTATION);
    double erroTHETA=sample_normal_distribution(SIGMA_FACTOR_ORI*STD_ORIENTATION);
    double erroPSI=sample_normal_distribution(SIGMA_FACTOR_ORI*STD_ORIENTATION);

    vx=vx+erroVX;
    vy=vy+erroVY;
    vz=vz+erroVZ;
    phi=phi+erroPHI;
    theta=theta+erroTHETA;
    psi=psi+erroPSI;

    vx=vx*elapsedTime;
    vy=vy*elapsedTime;
    vz=vz*elapsedTime;

    double J[6][6];
    J[0][0]= cos(psi)*cos(theta);
    J[0][1]=-sin(psi)*cos(phi)+cos(psi)*sin(theta)*sin(phi);
    J[0][2]= sin(psi)*sin(phi)+cos(psi)*sin(theta)*cos(phi);
    J[1][0]= sin(psi)*cos(theta);
    J[1][1]= cos(psi)*cos(theta)+sin(phi)*sin(theta)*sin(psi);
    J[1][2]=-cos(psi)*sin(phi)+sin(theta)*sin(psi)*cos(phi);
    J[2][0]=-sin(theta);
    J[2][1]= cos(theta)*sin(phi);
    J[2][2]= cos(theta)*cos(phi);

    this->pose.x=this->pose.x+vx*J[0][0]+vy*J[0][1]+vz*J[0][2];
    this->pose.y=this->pose.y+vx*J[1][0]+vy*J[1][1]+vz*J[1][2];
    this->pose.z=this->pose.z+vx*J[2][0]+vy*J[2][1]+vz*J[2][2];

    this->yawPitchRoll.x=phi;
    this->yawPitchRoll.y=theta;
    this->yawPitchRoll.z=psi;

}
