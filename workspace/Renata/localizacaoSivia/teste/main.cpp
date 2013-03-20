#include <QtGui/QApplication>
#include "teste.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Teste w;
    w.show();

    return a.exec();
}
