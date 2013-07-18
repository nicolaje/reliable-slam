#include "mainwindow.h"
#include <QApplication>
#include <eigen3/Eigen/Eigen>
#include <iostream>

using namespace Eigen;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    RowVector3d v;
    v<<1,2,3;
    std::cout << "v: " << v<<std::endl;

    Matrix3d m;
    m<<1,0,0,0,1,0,0,0,1;
    std::cout << "m: " <<m<<std::endl;

    std::cout<<"v*m: "<<v*m<<std::endl;

    std::cout<<"v*m*vT: "<<v*m*(v.transpose())+3<<std::endl;

    return a.exec();
}
