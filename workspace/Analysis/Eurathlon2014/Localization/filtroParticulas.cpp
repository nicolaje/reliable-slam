#include "filtroParticulas.h"

using namespace std;

FiltroParticulas::FiltroParticulas()
{
}



void FiltroParticulas::roleta( QVector <Particula> & populacao)
{
    QVector <Particula> populacaoAux;
    std::swap(populacao,populacaoAux);

    for(int index=0;index<populacaoAux.size();index++)
    {
        double numeroRoleta = (double)rand()/RAND_MAX;
        int index=-1;
        do
        {
            index++;
            if(index > populacaoAux.size()-1)
                index = populacaoAux.size()-1;
            numeroRoleta -= populacaoAux[index].peso;
        } while(numeroRoleta>0);

        populacao.push_back(populacaoAux[index]);
    }
}

void FiltroParticulas::criarPopulacao(IntervalVector searchSpace, QVector <Particula> & populacao, xyz yawPitchRoll)
{
       for(int k=0;k<TAMANHO_POPULACAO;k++)
       {
           Particula p;
           p.pose.x=p.fRand(searchSpace[0]);
           p.pose.y=p.fRand(searchSpace[1]);
           p.pose.z=p.fRand(searchSpace[2]);
           p.yawPitchRoll.x=p.fRandCentred(yawPitchRoll.xNoise,SIGMA_FACTOR_ORI*STD_ORIENTATION);
           p.yawPitchRoll.y=p.fRandCentred(yawPitchRoll.yNoise,SIGMA_FACTOR_ORI*STD_ORIENTATION);
           p.yawPitchRoll.z=p.fRandCentred(yawPitchRoll.zNoise,SIGMA_FACTOR_ORI*STD_ORIENTATION);
           populacao.push_back(p);

       }
   }

