#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QDebug>
#include "dados.h"
#include "configuracaoes.h"
#include "particula.h"
//#include "box.h"
#include "imagem.h"
#include <time.h>
#include <stdlib.h>
#include "paletacores.h"
//#include "interval.h"
#include "filtroParticulas.h"
#include "sivia.h"
#include "hibrido.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;



std::string stringalizar(double x)
{
    std::ostringstream oss;
    oss << x;
    return oss.str();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qDebug()<<"Carregar dados ...";
    //Dados do arquivo
    QVector <xyz> poseXYZ;
    QVector <xyz> yawPitchRoll;
    QVector <xyz> acelXYZ;
    QVector <xyz> velAng;
    QVector <xyz> velXYZ;
    QVector <QVector<transponder> > transponders;
    //QVector <Landmark> landmarksUsados;
    QVector < QVector <Landmark> > landmarksUsados;
    Dados dados;
    //    dados.localizacaoLandmarks(landmarksUsados);
    //    dados.carregarArquivo(poseXYZ, yawPitchRoll, acelXYZ, velAng, velXYZ, transponders);
    dados.carregarArquivo(poseXYZ, yawPitchRoll, acelXYZ, velAng, velXYZ, landmarksUsados);


    srand(time(NULL));

    Dados d;
    qDebug()<<"Salvando log com posicoes reais... conferir o nome";
    string nome = PATH_RESULTS + string(LOGREAIS);//string("logReaisAmbiente1traj1.csv");
    ofstream logReais(nome.c_str());
    for(int k=0;k<poseXYZ.size();k=k+LEITURAS_POR_TEMPO_LEITURAS){
        logReais<<d.stringalizar(poseXYZ[k].x)+";"+d.stringalizar(poseXYZ[k].y)+";"+d.stringalizar(poseXYZ[k].z)+";\n";
    }
    logReais.close();

    //     double _a[3][2]={{10,20},{10, 20},{10,20}};
    //     IntervalVector g(3,_a);
    //     doublle _b[3][2]={{5,15},{5, 15},{5,25}};
    //     IntervalVector b(3,_b);
    //     g=g&b;
    //     cout<<g<<endl;

    /*for(int i=0;i<10;i++){


        qDebug()<<"Iniciar Filtro de Particulas"<<i;
        //FiltroParticulas fp;
        //fp.executarFiltro(poseXYZ, yawPitchRoll, velXYZ, transponders, landmarksUsados,i);


        //Sivia s;
        double _x[3][2]={{mapaMinX,mapaMaxX},{mapaMinY, mapaMaxY},{mapaMinZ,mapaMaxZ}};
        IntervalVector searchSpace(3,_x);

        IntervalVector ambienteInicial(3,_x);

        //qDebug()<<"Iniciar SIVIA1"<<i;
        //s.executarLocalizacaoSivia1(searchSpace, ambienteInicial, poseXYZ,yawPitchRoll,velXYZ,transponders,landmarksUsados,i);

        //qDebug()<<"Iniciar Contratores"<<i;
        //s.executarLocalizacaoContratores(searchSpace, ambienteInicial, poseXYZ,yawPitchRoll,velXYZ,transponders,landmarksUsados,i);

        //qDebug()<<"Iniciar SIVIA2"<<i;
        //s.executarLocalizacaoSivia2(searchSpace, ambienteInicial, poseXYZ,yawPitchRoll,velXYZ,transponders,landmarksUsados,i);

        //Hibrido h;
        //qDebug()<<"Iniciar Hibrido Contratores"<<i;
        //h.executarLocalizacaoHibridaContratores(searchSpace,ambienteInicial, poseXYZ,yawPitchRoll,velXYZ,transponders,landmarksUsados,i);

        //qDebug()<<"Iniciar Hibrido SIVIA1"<<i;
        //h.executarLocalizacaoHibridaSivia1(searchSpace, ambienteInicial, poseXYZ,yawPitchRoll,velXYZ,transponders,landmarksUsados,i);

        //qDebug()<<"Iniciar Hibrido SIVIA2"<<i;
        //h.executarLocalizacaoHibridaSivia2(searchSpace, ambienteInicial, poseXYZ,yawPitchRoll,velXYZ,transponders,landmarksUsados,i);

    }*/

    qDebug()<<"Iniciar Hibrido Contratores";
    double _x[3][2]={{mapaMinX,mapaMaxX},{mapaMinY, mapaMaxY},{mapaMinZ,mapaMaxZ}};
    IntervalVector searchSpace(3,_x);
    IntervalVector ambienteInicial(3,_x);
    Hibrido h;
    h.executarLocalizacaoHibridaContratores(searchSpace,ambienteInicial, poseXYZ,yawPitchRoll,velXYZ,landmarksUsados,0);

    qDebug()<<"FIM";

    return a.exec();

}
