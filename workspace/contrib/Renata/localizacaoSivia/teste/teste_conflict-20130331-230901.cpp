#include "teste.h"
#include "ui_teste.h"

Teste::Teste(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Teste)
{
    ui->setupUi(this);
}

Teste::~Teste()
{
    delete ui;
}
