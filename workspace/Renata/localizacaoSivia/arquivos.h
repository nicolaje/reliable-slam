#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include "repere.h"
#include "landmark.h"

class arquivos
{
public:


    arquivos ();
    void oi();
    int carregarDadosLeiturasA(QString fileName, vector <pose> & infOdo, vector <vector<landmark> > & infDist, vector <pose> posLandmarks, double erro);
    int carregarDadosLandmarksA(QString fileName, vector <pose> & landmarks);
};
#endif // ARQUIVOS_H


