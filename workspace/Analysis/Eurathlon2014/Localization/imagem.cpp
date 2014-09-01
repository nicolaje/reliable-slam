#include "imagem.h"

Imagem::Imagem()
{
}

void Imagem::carregarImagem(QString caminhoTXT){
    this->qimg.load(caminhoTXT);
    if(this->qimg.isNull()==true){
        qDebug()<<"Não carregou o mapa"<<caminhoTXT;
    }
}
void Imagem::inicializarPaiter(){
    this->qpaiter=new QPainter();
    this->qpaiter->begin(& this->qimg);
}
void Imagem::salvarImagem(QString caminhoEnome){
    this->qimg.save(caminhoEnome,"BMP",100);
}
void Imagem::finalizarPainter(){
    this->qpaiter->end();
}

double Imagem::xToPix(double x)
{
    double aux = this->qimg.width()/(mapaMaxX-mapaMinX);
    return (x-mapaMinX)*aux;
}

double Imagem::yToPix(double y){
    double aux = this->qimg.height()/(mapaMaxY-mapaMinY);
    return this->qimg.height()-((y-mapaMinY)*aux);

}

double Imagem::distanciaToPix(double d){//considerando que o mapa tem pix/metro proporcional em todos os eixos
    return d*(this->qimg.width()/abs(mapaMaxX-mapaMinX));
}

void Imagem::desenhaCaixa2(double xinf, double xsup, double yinf, double ysup, QColor pen, QBrush brush){
    this->qpaiter->setPen(pen);
    this->qpaiter->setBrush(brush);

    xinf=xToPix(xinf);
    yinf=yToPix(yinf);
    xsup=xToPix(xsup);
    ysup=yToPix(ysup);
    QVector<QPointF> pontos;
    pontos.push_back(QPointF(xinf,yinf));
    pontos.push_back(QPointF(xinf,ysup));
    pontos.push_back(QPointF(xsup,ysup));
    pontos.push_back(QPointF(xsup,yinf));
    this->qpaiter->drawPolygon(QPolygonF(pontos));

    //this->qpaiter->drawRect(QRectF(xToPix(xinf),yToPix(yinf),distanciaToPix(xsup-xinf),distanciaToPix(ysup-yinf)));
    //this->qpaiter->drawRect(QRectF(xToPix(xinf),yToPix(yinf),distanciaToPix(abs(xinf-xsup)),distanciaToPix(abs(yinf-ysup))));
}
void Imagem::desenhaElipse2(double x, double y, double rx, double ry, QColor pen, QBrush brush){
    this->qpaiter->setPen(pen);
    this->qpaiter->setBrush(brush);
    this->qpaiter->drawEllipse(QPointF(xToPix(x),yToPix(y)),distanciaToPix(rx),distanciaToPix(ry));
}

void Imagem::desenhaLinha2(double x, double y, double x2, double y2){
    x=(int)xToPix(x);
    x2=(int)xToPix(x2);
    y=(int)yToPix(y);
    y2=(int)yToPix(y2);

    if(x<=0 || x>=qimg.width() || y<=0 || y>=qimg.height()){
        //qDebug()<<"|Fora imagem";
    }else{
        this->qpaiter->setPen(Qt::lightGray);
        this->qpaiter->drawLine(QPoint(x,y),QPoint(x2,y2));
    }
}
