#ifndef IMAGEM_H
#define IMAGEM_H
#include <QImage>
#include <QPainter>
#include <QDebug>
#include "configuracaoes.h"

class Imagem
{
public:
    QImage qimg;
    QPainter *qpaiter;
    QBrush qbrush;
    QPen qpen;
public:
    Imagem();
    void carregarImagem(QString caminhoTXT);
    void inicializarPaiter();
    void salvarImagem(QString caminhoEnome);
    void finalizarPainter();
    double xToPix(double x);
    double yToPix(double y);
    double distanciaToPix(double d);
    void desenhaCaixa2(double xinf,double xsup,double yinf, double ysup, QColor pen, QBrush brush);
    void desenhaElipse2(double x,double y,double rx, double ry, QColor pen, QBrush brush);
    void desenhaLinha2(double x, double y,double x2, double y2);
};

#endif // IMAGEM_H
