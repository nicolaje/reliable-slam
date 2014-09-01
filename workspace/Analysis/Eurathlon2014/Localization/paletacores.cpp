#include "paletacores.h"

PaletaCores::PaletaCores()
{
    max = 100;
    porcento = 0;
    subindo = true;

    cores.push_back(new QColor(240,240,0));
    cores.push_back(new QColor(255,0,0));



    cor = new QColor(255,0,255); //Cor inicial
}

void PaletaCores::updateCor()
{

    if (subindo)
    {
        porcento++;
    }
    else
    {
        porcento--;
    }

    if (porcento >= max)
    {
        subindo = false;
        porcento = max;
    }
    else if (porcento <= 0)
    {
        subindo = true;
        porcento = 0;
    }

    this->updatePorcentagem((double)porcento / max);

}
void PaletaCores::updatePorcentagem(double percent)
{
    double pos = (double) (cores.size()-1) * percent;
    double p2 = pos - (double)floor(pos);


    cor->setRedF(  cores[floor(pos)]->redF()   + (double)( cores[ceil(pos)]->redF()   - cores[floor(pos)]->redF()   ) * p2);
    cor->setGreenF(cores[floor(pos)]->greenF() + (double)( cores[ceil(pos)]->greenF() - cores[floor(pos)]->greenF() ) * p2);
    cor->setBlueF( cores[floor(pos)]->blueF()  + (double)( cores[ceil(pos)]->blueF()  - cores[floor(pos)]->blueF()  ) * p2);

}
