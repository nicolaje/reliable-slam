#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "time.h"
#include "cmath"

#include <random>
#include <cstdio>
#include <windows.h>

#define ERRO_SENSOR 0.3
#define ERRO_POS_MARK 0.1
#define ALCANCE_LASER 10

double xmin,xmax,ymin,ymax;
double epsilon;

struct solucao{
    vector <box>caixas;
    particula real;
    particula estimada;
    vector <particula> particulas;
};

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    xmin=0;xmax=20;//xmin=-10;xmax=10;
    ymin=0;ymax=20;//ymin=-10;ymax=10;
    R=new repere(this,ui->graphicsView,xmin,xmax,ymin,ymax);
}

void MainWindow::Init()
{ epsilon=ui->EpsilonSpinBox->value();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*iboolean Inside (box& X)
{
    interval F=Sqrt(Sqr(X[1])+Sqr(X[2]));
    return (In(F,interval(1,2)));

    //interval F=Sqrt(Sqr(X[1])+Sqr(X[2]));
    //interval F2=Sqrt(Sqr(X[1]+1)+Sqr(X[2]+1));
    //return (In(F,interval(1,2)) && In(F2,interval(1,2)));

};*/

iboolean Inside3 (box& X, vector<landmark>  & infDist)//renata
{
    int i;
    vector<interval> F;
    for(i=0;i<infDist.size();i++){
        landmark aux=infDist[i];
        interval x=interval(aux.pos.x-ERRO_POS_MARK,aux.pos.x+ERRO_POS_MARK);
        interval y=interval(aux.pos.y-ERRO_POS_MARK,aux.pos.y+ERRO_POS_MARK);
        F.push_back(Sqrt(Sqr(X[1]-x)+Sqr(X[2]-y)));
    }
    iboolean result;
    if(F.size()>1){
        result=(In(F[0],infDist[0].dist) && In(F[1],infDist[1].dist));
        for(i=2;i<F.size();i++){
            result=(In(F[i],infDist[i].dist) && result);
        }
    }else{
        result=(In(F[0],infDist[0].dist));
    }
    return (result);
};


int carregarDadosLandmarks(QString fileName, vector <pose> & landmarks){
/*cada linha tem
posX posY posTh*/
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
       return 1;

    QString aux;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list =line.split(" ");
        pose l;
        aux=list[0];
        l.x=aux.toDouble();
        aux=list[1];
        l.y=aux.toDouble();
        landmarks.push_back(l);
    }

    file.close();
    return 0;
}

int carregarDadosLeituras(QString fileName, vector <pose> & infOdo, vector <vector<landmark> > & infDist, vector <pose> posLandmarks){
/*
odoX odoY odoTh
landX distX landY distY landZ distZ ...
*/
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
       return 1;

    QString aux;
    QTextStream in(&file);
    int cont=0;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list =line.split(" ");
        if(cont%2==0){//linhas com odometria
            pose odom;
            aux=list[0];
            odom.x=aux.toDouble();
            aux=list[1];
            odom.y=aux.toDouble();
            aux=list[2];
            odom.th=aux.toDouble();
            infOdo.push_back(odom);
        }
        else{//linhas com landmarks e distâncias
            vector <landmark> visualizacao;
            for(int i=0;i<list.size();i=i+2){
                landmark lm;
                aux=list[i];
                lm.pos=posLandmarks[aux.toInt()];
                aux=list[i+1];
                lm.dist=interval(aux.toDouble()-ERRO_SENSOR, aux.toDouble()+ERRO_SENSOR);
                visualizacao.push_back(lm);
            }
            infDist.push_back(visualizacao);
        }
        cont++;
    }

    file.close();
    return 0;

}

int carregarDadosOLM(QString fileName, vector <pose> & infOdo, vector <vector<landmark> > & infDist, vector <pose> posLandmarks, vector <vector<double> > & laser){
/*
o odoX odoY odoTh
l l1 l2 l3 l4 l5 ...
m landX distX landY distY landZ distZ ...
*/
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
       return 1;

    QString aux;
    QTextStream in(&file);
    //int cont=0;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        line=line.trimmed();
        QStringList list =line.split(" ");
        if(list[0]=="o"){//linhas com odometria
            pose odom;
            aux=list[1];
            odom.x=aux.toDouble();
            aux=list[2];
            odom.y=aux.toDouble();
            aux=list[3];
            odom.th=aux.toDouble();
            infOdo.push_back(odom);
        }
        else if(list[0]=="l"){//linhas com distâncias do laser
            vector <double> l;
            for(int i=1;i<list.size();i++){
                l.push_back(list[i].toDouble());
            }
            laser.push_back(l);
        }
        else if(list[0]=="m"){//linhas com landmarks e distâncias
            vector <landmark> visualizacao;
            for(int i=1;i<list.size();i=i+2){
                landmark lm;
                aux=list[i];
                //qDebug()<<aux.toInt();
                lm.pos=posLandmarks[aux.toInt()];
                aux=list[i+1];
                lm.dist=interval(aux.toDouble()-ERRO_SENSOR, aux.toDouble()+ERRO_SENSOR);
                visualizacao.push_back(lm);
            }
            infDist.push_back(visualizacao);
        }
        //cont++;
    }

    file.close();
    return 0;

}

int carregarDadosObstaculos(QString fileName, vector<QGraphicsPolygonItem*> & obstaculos, repere & R){
/*
x y  x1 y1  x2 y2
*/
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
       return 1;
    QString aux;
    QTextStream in(&file);
    //int cont=0;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        line=line.trimmed();
        QStringList list =line.split("  ");

        QPolygonF obs1;
        for(int i=0;i<list.size();i++){
            QStringList list2 =list[i].split(" ");
            obs1 << QPointF(R.xToPix(list2[0].toDouble()),R.yToPix(list2[1].toDouble()));
        }
        QGraphicsPolygonItem* P;
        P=R.Scene->addPolygon(obs1,QPen(Qt::darkRed),QBrush(Qt::darkRed));
        obstaculos.push_back(P);
    }

    file.close();
    return 0;

}

double fRand(double fMin, double fMax)
{
    fMin=fMin-0.0001;
    fMax=fMax-0.0001;
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);

}

double randNormal(double inMean, double inStdDev){
    double retorno=0;
    while (retorno==0 || (retorno>inStdDev) || (retorno<(inStdDev*-1))){
        double fac, rsq, v1, v2,gset;
        int iset=0;
        retorno=0;
    if(iset == 0) {
           do {
               v1 = 2.0*(0+((double)rand() / RAND_MAX)*1) - 1.0;
               v2 = 2.0*(0+((double)rand() / RAND_MAX)*1) - 1.0;
              rsq = v1*v1+v2*v2;
           } while(rsq >= 1.0 || rsq == 0);
           fac = sqrt(-2.0*log(rsq)/rsq);
           gset = v1*fac;
           iset = 1;
           retorno= (v2*fac*inStdDev + inMean);
    } else {
           iset = 0;
           retorno= (gset*inStdDev + inMean);
        }
}
return retorno;
}

double tempo(clock_t inicio){
    clock_t fim;
    fim=clock();
    double t=(double)(fim - inicio)/CLOCKS_PER_SEC;
    return t;
}

double sample(double b){
    double r=0;

    for(int i=0;i<12;i++){
        double f = (double)rand() / RAND_MAX;
        r=r+((b*-1) + f * (b - (b*-1)));
    }
    return r/2;
}

int testaLocalizacao(double px, double py ,vector <box> caixas){

    for(int k=0;k<caixas.size();k++){
        box c;
        c=caixas[k];
        if(c[2].inf<=py && py<= c[2].sup){
            if(c[1].inf<=px && px<= c[1].sup){
                return 1;
            }
        }
    }
    return 0;
}

void mostrarSolucaoFinal(vector <solucao> SolucaoFinal, repere & R){
    R.Scene->clear();
    for (int s=0;s<SolucaoFinal.size();s++){
        vector <box> caixas;
        caixas.swap(SolucaoFinal[s].caixas);
        for (int i=0;i<caixas.size();i++){
            box b=caixas[i];
            R.DrawBox(b[1],b[2],QPen(Qt::darkGray),QBrush(Qt::darkGray));
        }
        R.DrawEllipse(R.pixToX(SolucaoFinal[s].real.pos.x),R.pixToY(SolucaoFinal[s].real.pos.y),0.1,QPen(Qt::yellow),QBrush(Qt::yellow));
        R.DrawEllipse(R.pixToX(SolucaoFinal[s].estimada.pos.x),R.pixToY(SolucaoFinal[s].estimada.pos.y),0.1,QPen(Qt::blue),QBrush(Qt::blue));
    }
}

void leituraParticula(particula p, double maxDist, repere & R,vector<QGraphicsPolygonItem*> & obstaculos, vector<double> & leituras){
    double x1,x2,x3,y1,y2,y3;
    for(int m=-90;m<90;m=m+10){//cria laser
        x1=maxDist*cos(m*M_PI/180);
        y1=maxDist*sin(m*M_PI/180);
        x2=((x1*cos(p.pos.th*M_PI/180))-(y1*sin(p.pos.th*M_PI/180)));
        y2=((x1*sin(p.pos.th*M_PI/180))+(y1*cos(p.pos.th*M_PI/180)));
        x3=p.pos.x+x2;
        y3=p.pos.y+y2;

        QGraphicsLineItem *l;
        l=R.Scene->addLine(p.pos.x,p.pos.y,x3,y3,QPen(Qt::red));
        double dist=p.Distancia(obstaculos,l,p);
        if(dist!=-1){
            dist=R.ConvDistPixToCoor(dist);
        }
        leituras.push_back(dist);
        R.Scene->removeItem(l);

    }//for leituras
}


void MainWindow::on_ButtonStart_clicked()
{
    Init();
    clock_t inicializacao=clock();
    srand(time(NULL));
    vector <solucao> SolucaoFinal;
    list<box> L;
    int k=0;

    //arquivos txt;
    qDebug()<<"Carrega arquivos";
    vector <pose> landmarks;
    carregarDadosLandmarks("dadosLandmarks2.txt", landmarks);
    R->desenhaLandmarks(landmarks);

    vector <pose> infOdo;
    vector <vector<landmark> > infDist;
    vector <vector<double> >laser;
    carregarDadosOLM("dadosOLM2.txt",infOdo,infDist,landmarks,laser);

    //obstaculos
    vector<QGraphicsPolygonItem*> obstaculos;
    carregarDadosObstaculos("dadosObstaculos2.txt",obstaculos,*R);

    qDebug()<<"Tempo Inicialização:"<<tempo(inicializacao);
    clock_t inicio=clock();

      vector <particula> particulas;
      int partElim;
      int partCriadas=0;
      //for(int i=1;i<2;i++){
      for(int i=0;i<infDist.size();i++){
          clock_t porLeitura=clock();
          solucao solucao;
          qDebug();
//{***************CRIA CAIXAS

          vector <box> caixas;
          caixas.clear();
          k=0;
          box X(interval(xmin,xmax),interval(ymin,ymax));
          L.push_back (X);
//if(infDist.size()>0){
          qDebug()<<"Cria caixas. Posição:"<<i;
          while ( !L.empty() )
                {   k++;
                    X=L.front();   L.pop_front();
                    iboolean test=Inside3(X,infDist[i]);
                    if (X.Width()<epsilon)     {
                        R->DrawBox(X[1],X[2],QPen(Qt::darkGray),QBrush(Qt::darkGray));
                        caixas.push_back(X);
                    }
                    else if ( test==itrue )    {
                        R->DrawBox(X[1],X[2],QPen(Qt::darkGray),QBrush(Qt::lightGray));
                        caixas.push_back(X);
                    }
                    else if (test==ifalse)     {}//R->DrawBox(X[1],X[2],QPen(Qt::darkBlue),QBrush(Qt::cyan));
                    else
                    {
                        box X1(2);  box X2(2);
                        Bisect (X,X1,X2);
                        L.push_back(X1);  L.push_back(X2);
                    }
                }
          solucao.caixas=caixas;
//}
//}***************CRIA CAIXAS

          if(i==0){//crio partículas

              //particula 0 é o robo real
              particula robo;
              robo.pos.x=R->xToPix(infOdo[i].x);
              robo.pos.y=R->yToPix(infOdo[i].y);
              robo.pos.th=infOdo[i].th;
              robo.sit=2;
              robo.id=-1;
              particulas.push_back(robo);

              partCriadas=0;
              int c=1;
              int t=0;
              for(int j=0;j<caixas.size();j++){
                  int npart;
                  box aux=caixas[j];
                  //define nro de partículas por caixa
                  if(Width(aux)<0.1 && c<1){c++;npart=0;}
                   else if(Width(aux)<=0.1 && c>=1){
                      npart=(int)(((Width(aux[1])*100)*(Width(aux[2])*100))*0.02);
                      //npart=1;
                      if(npart<1)npart=1;
                      c=0;
                  }
                  else {
                      npart=(int)(((Width(aux[1])*100)*(Width(aux[2])*100))*0.02);
                      //npart=1;
                      if(npart<1)npart=1;
                  }

                  partCriadas=partCriadas+npart;
                  partElim=0;//partCriadas;
                  for(int k=0;k<npart;k++){//cria e desenha particulas
                      particula p;
                      p.pos.x=R->xToPix(fRand(aux[1].inf,aux[1].sup));
                      p.pos.y=R->yToPix(fRand(aux[2].inf,aux[2].sup));
                      p.pos.th=fRand(-179,179);
                      p.sit=1;
                      p.id=t;t++;
                      particulas.push_back(p);
                      R->Scene->addLine(p.pos.x,p.pos.y,p.pos.x,p.pos.y,QPen(Qt::red));//desenha partícula

                  }
              }

/*
              //////
              double normalizar=0;
              for(int h=0;h<particulas.size();h++){
                  vector <double> l;
                  double dif=1;
                  //qDebug()<<"part "<<particulas[h].pos.x;
                  leituraParticula(particulas[h],R->ConvDistCoorToPix(ALCANCE_LASER),*R,obstaculos,l);
                  //com gaussiana
                  double desvio=5;
                  for(int m=0;m<l.size();m++){
                      dif=dif*((1/sqrt(2*M_PI*pow(desvio,2))*exp(-pow(l[m]-laser[0][m],2)/(2*pow(desvio,2)))));
                      //qDebug()<<"dif"<<l[m]<<laser[0][m];
                  }
                  particulas[h].peso=dif;
                  qDebug()<<"peso"<<particulas[h].peso;

                  normalizar=normalizar+dif;
            }
double peso=0;
              int tam=particulas.size();
              vector<particula>::iterator it;
              for(it=particulas.begin();it<particulas.end();it.operator ++()){
                  (*it).peso=(*it).peso/normalizar;
                  peso=peso+(*it).peso;
                  qDebug()<<"peso n"<<(*it).peso<<normalizar;
                  if((*it).peso<(1.0/tam*0.5)){
                      particulas.erase(it);
                      it.operator --();
                  }
                  else{
                      R->Scene->addLine((*it).pos.x,(*it).pos.y,(*it).pos.x,(*it).pos.y,QPen(Qt::red));//desenha partícula
                  }
              }
              double x=1.0/30;
            qDebug()<<"depois"<<particulas.size()<<peso;

*/
              qDebug()<<partCriadas<<"particulas criadas";
          }else{//movimento partículas

              partElim=partCriadas;
              //particula 0 é o robo real
              particulas[0].pos.x=R->xToPix(infOdo[i].x);
              particulas[0].pos.y=R->yToPix(infOdo[i].y);
              particulas[0].pos.th=infOdo[i].th;
              particulas[0].sit=2;
              particulas[0].id=-1;

              //MODELO DE MOVIMENTO do probabilistic robotics
              //teste: alf1=0.01 afeta o angulo, alf2=0.00001 afeta muito o angulo, alf3=0.0015 afeta tudo, alf4=0.0001 afeta muito tudo
              double alf1=0,alf2=0,alf3=0,alf4=0;
              double rot1=atan2((R->yToPix(infOdo[i].y)-R->yToPix(infOdo[i-1].y)),(R->xToPix(infOdo[i].x)-R->xToPix(infOdo[i-1].x)))-infOdo[i-1].th;
              double trans=sqrt(pow((R->xToPix(infOdo[i-1].x)-R->xToPix(infOdo[i].x)),2)+pow((R->yToPix(infOdo[i-1].y)-R->yToPix(infOdo[i].y)),2));
              double rot2=infOdo[i].th-infOdo[i-1].th-rot1;

              for(int j=1;j<particulas.size();j++){

                  if(particulas[j].sit!=0){
                      double Drot1=rot1-(sample(alf1*pow(rot1,2)+alf2*pow(trans,2)));
                      double Dtrans=trans-(sample(alf3*pow(trans,2)+alf4*pow(rot1,2)+alf4*pow(rot2,2)));
                      double Drot2=rot2-(sample(alf1*pow(rot2,2)+alf2*pow(trans,2)));

                      particulas[j].pos.x=particulas[j].pos.x+Dtrans*cos(particulas[j].pos.th+Drot1);
                      particulas[j].pos.y=particulas[j].pos.y+Dtrans*sin(particulas[j].pos.th+Drot1);
                      particulas[j].pos.th=round(particulas[j].pos.th+Drot1+Drot2);

                      ///////////////////////////
                      while(particulas[j].pos.th<-180 || particulas[j].pos.th>180){
                          if(particulas[j].pos.th<-360){
                              particulas[j].pos.th=360+particulas[j].pos.th;
                          }
                          if(particulas[j].pos.th>360){
                              particulas[j].pos.th=particulas[j].pos.th-360;
                          }
                          if(particulas[j].pos.th <= 360 && particulas[j].pos.th >= -360){

                              if(particulas[j].pos.th > 0){
                                  particulas[j].pos.th = particulas[j].pos.th - 360;
                              }
                              else if(particulas[j].pos.th < 0){
                                  particulas[j].pos.th=360+particulas[j].pos.th;
                              }
                          }
                      }
                      if (particulas[j].pos.th>180 || particulas[j].pos.th<-180)
                          qDebug()<<"Errado "<<particulas[j].pos.x<<particulas[j].pos.y<<particulas[j].pos.th<< Drot1<<Drot2;
                      //////////////////


                      //descarta partículas fora das caixas
                      if(testaLocalizacao(R->pixToX(particulas[j].pos.x),R->pixToY(particulas[j].pos.y),caixas)==1){
                          particulas[j].sit=1;
                          partElim--;
                          R->Scene->addLine(particulas[j].pos.x,particulas[j].pos.y,particulas[j].pos.x,particulas[j].pos.y,QPen(Qt::red));//desenha partícula
                      }else{
                          particulas[j].sit=0;
                          R->Scene->addLine(particulas[j].pos.x,particulas[j].pos.y,particulas[j].pos.x,particulas[j].pos.y,QPen(Qt::black));//desenha partícula
                      }
                  }
              }
          }

          qDebug()<<"Libera espaço das partículas eliminadas";
          //LIMPA VETOR DE PARTÍCULAS
          vector<particula>::iterator it;
          for(it=particulas.begin();it<particulas.end();it.operator ++()){
              if((*it).sit==0){
                  particulas.erase(it);
                  it.operator --();
              }
          }

//{*********************LEITURA DAS PARTÍCULAS (LASER) - probabilidades, normaliza, acha melhor, elimina as fora de caixas
          vector<double> leiturasRobo=laser[i];
          //qDebug()<<leiturasRobo[0];

          double normalizar=0;
          for(int j=1;j<particulas.size();j++){
              double x1,x2,x3,y1,y2,y3,maxDist;
              maxDist=R->ConvDistCoorToPix(ALCANCE_LASER);
              vector<double> leituras;
              double dif=1;

              for(int m=-90;m<90;m=m+10){//cria laser
                  x1=maxDist*cos(m*M_PI/180);
                  y1=maxDist*sin(m*M_PI/180);
                  x2=((x1*cos(particulas[j].pos.th*M_PI/180))-(y1*sin(particulas[j].pos.th*M_PI/180)));
                  y2=((x1*sin(particulas[j].pos.th*M_PI/180))+(y1*cos(particulas[j].pos.th*M_PI/180)));
                  x3=particulas[j].pos.x+x2;
                  y3=particulas[j].pos.y+y2;

                  QGraphicsLineItem *l;
                  l=R->Scene->addLine(particulas[j].pos.x,particulas[j].pos.y,x3,y3,QPen(Qt::red));
                  double dist=particulas[j].Distancia(obstaculos,l,particulas[j]);
                  if(dist!=-1){
                      dist=R->ConvDistPixToCoor(dist);
                  }
                  leituras.push_back(dist);
                  R->Scene->removeItem(l);

              }//for leituras

              //leituraParticula(particulas[j],maxDist,*R,obstaculos, leituras);

              //if(j==0)leiturasRobo=leituras;

              /*for(int m=0;m<leituras.size();m++){
                  double aux;
                  double l=leituras[m];
                  double lr=leiturasRobo[m];
                  aux=l-lr;
                  if(aux==0)aux=1;
                  dif=dif*fabs(aux);
              }
              particulas[j].peso=dif;
*/
              //com gaussiana
              double desvio=10;
              for(int m=0;m<leituras.size();m++){
                  double l=leituras[m];
                  double lr=leiturasRobo[m];
                  dif=dif*(1/sqrt(2*M_PI*pow(desvio,2))*exp(-pow(l-lr,2)/(2*pow(desvio,2))))*10000;
              }
              particulas[j].peso=dif;
              //qDebug()<<dif;
              if(j!=0) normalizar=normalizar+dif;
          }

          qDebug()<<"Normaliza peso das partículas e busca a melhor";
          if(normalizar<=0){
              qDebug()<<"divisão por 0 não pode"<< normalizar;
          }else{
              int melhor=0;
              for(int h=1;h<particulas.size();h++){
                      particulas[h].peso=particulas[h].peso/normalizar;

                      qDebug()<<"p "<<h<<R->pixToX(particulas[h].pos.x)<<R->pixToY(particulas[h].pos.y)<<particulas[h].pos.th<<particulas[h].peso;

                      if(melhor==0 || particulas[h].peso>=particulas[melhor].peso){
                          melhor=h;
                      }
              }
              solucao.particulas=particulas;



              int b=0;
              qDebug()<<"Substitui partículas eliminadas";
              //substitui as eliminadas
              for(int h=0;h<partElim;h++){
                  particula p=particulas[melhor];
                  p.pos.x=p.pos.x+fRand(-10,10);
                  p.pos.y=p.pos.y+fRand(-10,10);
                  p.pos.th=p.pos.th+round(fRand(-10,10));
                  if(testaLocalizacao(R->pixToX(p.pos.x),R->pixToY(p.pos.y),caixas)==1)
                  particulas.push_back(p);
                  else {
                      h--;
                      b++;
                      if(b>3){
                          particulas.push_back(p);
                          h++;
                          b=0;
                      }
                  }
              }
              partElim=0;

              /*
              //ideia heinrich para substituir as eliminadas
              double r=fRand(0,(1/partElim));
              double c=particulas[1].peso;
              int ind=1;
              for(int m=0; m<partElim;m++){
                  double U=r=(m-1)*(1/partElim);
                  while(U>c){
                      ind=ind+1;
                      c=c+particulas[ind].peso;
                  }
                  particulas.push_back(particulas[ind]);
              }
*/

              //vector<particula>::iterator it;
              /*for(it=particulas.begin();it<particulas.end();it.operator ++()){
                       qDebug()<<"(x,y,th)=("<<(*it).pos.x<<(*it).pos.y<<(*it).pos.th<<") sit: "<<(*it).sit<<" id: "<<(*it).id;
              }*/

              //desenha posição do robo e da partícula
              R->DrawEllipse(R->pixToX(particulas[0].pos.x),R->pixToY(particulas[0].pos.y),0.1,QPen(Qt::yellow),QBrush(Qt::yellow));
              R->DrawEllipse(R->pixToX(particulas[melhor].pos.x),R->pixToY(particulas[melhor].pos.y),0.1,QPen(Qt::blue),QBrush(Qt::blue));

              //Mostra melhor
              qDebug()<<"Resposta";
              //qDebug()<<"melhor"<<particulas[melhor].pos.x<<particulas[melhor].pos.y<<particulas[melhor].pos.th;
              //qDebug()<<"real"<<particulas[0].pos.x<<particulas[0].pos.y<<particulas[0].pos.th;
              //qDebug()<<"real (x,y,th)=("<<particulas[0].pos.x<<particulas[0].pos.y<<particulas[0].pos.th<<") sit: "<<particulas[0].sit<<" id: "<<particulas[0].id;
              //qDebug()<<"melhor(x,y,th)=("<<particulas[melhor].pos.x<<particulas[melhor].pos.y<<particulas[melhor].pos.th<<") sit: "<<particulas[melhor].sit<<" id: "<<particulas[melhor].id<<" peso: "<<particulas[melhor].peso;

              solucao.real=particulas[0];
              solucao.estimada=particulas[melhor];

              qDebug()<<"melhor"<<R->pixToX(particulas[melhor].pos.x)<<R->pixToY(particulas[melhor].pos.y)<<particulas[melhor].pos.th<<particulas[melhor].peso;
              qDebug()<<"real"<<R->pixToX(particulas[0].pos.x)<<R->pixToY(particulas[0].pos.y)<<particulas[0].pos.th;

              int cont=0;
              for(int j=0;j<particulas.size();j++){
                  if(particulas[j].sit==1 || particulas[j].sit==-1)
                  cont++;
              }
              qDebug()<<"cont"<<cont;
              qDebug()<<"particulas size"<<particulas.size();


              //R->Scene->clear();
              //R->att(strcat("zz","1"),solucao.real,solucao.estimada,solucao.caixas,obstaculos);
              //R->Save(strcat("z","1"));
          }

//}*********************LEITURA DAS PARTÍCULAS (LASER)

          qDebug()<<"Tempo por leitura:"<<tempo(porLeitura);
          SolucaoFinal.push_back(solucao);
      }

      qDebug() << "Number of boxes "<<k;    

      R->Save("paving");


      qDebug()<<"Tempo Total:"<<tempo(inicio);


}
