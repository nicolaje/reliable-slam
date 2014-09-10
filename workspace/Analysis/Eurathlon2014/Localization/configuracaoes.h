//#ifndef CONFIGURACAOES_H
#define CONFIGURACAOES_H
#pragma once


#define DATASET "../trajetoriasDissertacao/1trans/traj02.csv";
#define DATASET_TRANSPONDERS "../trajetoriasDissertacao/2trans/default.pos"
#define MAPA "../mapas/mapa1000x1000.bmp";
#define PATH_RESULTS "../resultados/"
#define LOGREAIS "logReaisAmb1Traj4.csv"
#define NRO_TRANSPONDERS 1

struct xyz{
    double x;
    double y;
    double z;
    double xNoise;
    double yNoise;
    double zNoise;
};

struct transponder{
    double dist;
    double distNoise;
};
//#define DIMENSOES 2

//inst1
#define mapaMinX -300 //-100
#define mapaMaxX 300
#define mapaMinY -300
#define mapaMaxY 300
#define mapaMinZ -21.2 //-40
#define mapaMaxZ -18.8



#define EPSILON 0.5

//normalmente 1 e 10
#define TEMPO_LEITURAS 0.1 //*1=uma leitura a cada 1s /0.1 =uma leitura a cada 0.1s
#define LEITURAS_POR_TEMPO_LEITURAS 1 //10 = uma leitura por segundo

//#define SIGMA_FACTOR 0.5
#define SIGMA_FACTOR_VEL 4      //influencia junto com STD_VEL_DOPPLER para achar o erro na velocidade
#define SIGMA_FACTOR_ORI 4      //influencia junto com STD_ORIENTATION para achar o erro na orientacao
#define SIGMA_FACTOR_TRA 4      //influencia junto com STD_DIST_TRANSP para achar o erro na dist dos transponders
#define STD_ORIENTATION 0.02    //desvio padrão dado na simulacao
#define STD_VEL_DOPPLER 0.04    //desvio padrão dado na simulacao
#define STD_DIST_TRANSP 0.3    //desvio padrão dado na simulacao

#define ERRO_DEEP 2.
#define ERRO_GPS 10.

#define MAX_TIME_FOR_OLD_READING 2. //seconds

#define TAMANHO_POPULACAO 1000
#define DESVIO_PADRAO_PESO_PARTICULAS 25 //ou um desvio alto, ou usa soma nos pesos, ou um desvio baixo mas com uma população tamanho monstro

