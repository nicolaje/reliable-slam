#ifndef TESTE_H
#define TESTE_H

#include <QMainWindow>

namespace Ui {
    class Teste;
}

class Teste : public QMainWindow
{
    Q_OBJECT

public:
    explicit Teste(QWidget *parent = 0);
    ~Teste();

private:
    Ui::Teste *ui;
};

#endif // TESTE_H
