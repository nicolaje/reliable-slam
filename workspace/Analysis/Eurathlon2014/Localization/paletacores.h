#ifndef PALETACORES_H
#define PALETACORES_H

#include <iostream>
#include <math.h>
#include <vector>
#include <QColor>

using namespace std;

class PaletaCores
{
public:
    PaletaCores();
    void updateCor();
    void updatePorcentagem(double percent);
    QColor *cor;
    int max;
private:
    vector<QColor*> cores;
    int porcento;
    bool subindo;
};

#endif // PALETACORES_H
