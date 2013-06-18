#include <QApplication>
#include "mainwindow.h"
#include <ibex/ibex.h>
#include <QDebug>

using namespace ibex;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    MORSEDataParser p();

//    IntervalVector test(2);
//    test[0]=Interval(0,1);
//    test[1]=Interval(3,4);
    Interval test=sqr(Interval(0,1)+Interval(3,4));

    qDebug() << "test: "<<test.lb()<< ", "<<test.ub();

    return a.exec();
}
