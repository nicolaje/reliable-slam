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

    Vector3d v1(1,1,1),v2(0.5,0.6,0.7);
    std::cout << v2(1) << ";" << v2(2) << std::endl;
//    std::cout << v1 << std::endl;
//    Vector3d vec=v1.cwise()*v;
//    std::cout << vec << std::endl;
    std::cout << v1.transpose() << std::endl;

    return a.exec();
}
