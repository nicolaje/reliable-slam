
#include "arquivos.h"


//*********************************************************************
//******************       CONSTRUCTEURS         **********************
//*********************************************************************
arquivos::arquivos()
{
}

void oi(){
    qDebug()<<"oi";
}

int carregarDadosLeiturasA(QString fileName, vector <pose> & infOdo, vector <vector<landmark> > & infDist, vector <pose> posLandmarks, double erro){
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
                lm.dist=interval(aux.toDouble()-erro, aux.toDouble()+erro);
                visualizacao.push_back(lm);
            }
            infDist.push_back(visualizacao);
        }
        cont++;
    }
    /*qDebug()<< "odo";
    for(int i=0;i<infOdo.size();i++){
        qDebug()<< infOdo[i].x<<" "<< infOdo[i].y;
    }
    qDebug()<< "dist";
    for(int j=0;j<infDist.size();j++){
        vector <lmVis> a = infDist[j];
        for(int i=0;i<a.size();i++){
            qDebug()<< a[i].pos.x<<" "<< a[i].pos.y<< "intervalo "<<a[i].dist.inf<<" "<<a[i].dist.sup;
        }
    }*/

    file.close();
    return 0;

}

int carregarDadosLandmarksA(QString fileName, vector <pose> & landmarks){
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
