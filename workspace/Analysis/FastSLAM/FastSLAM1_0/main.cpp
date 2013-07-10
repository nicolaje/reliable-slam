#include <QApplication>
#include <iostream>
#include "mainwindow.h"
#include <eigen3/Eigen/Eigen>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Eigen::MatrixXd m(2,5);
    m.resize(4,3);
    std::cout << "test" << std::endl;
    std::cout << "The matrix m is of size " << m.rows() << "x" << m.cols() << std::endl;
    m << 1,0,0,0,1,0,0,0,1,0,0,0 ;
    Eigen::VectorXd v(2);
    v.resize(5);
    std::cout << "The vector v is of size " << v.size() << std::endl;
    std::cout << "As a matrix, v is of size "
              << v.rows() << "x" << v.cols() << std::endl;
    v.resize(3);
    v << 1,0,0;
    std::cout << m*v<< std::endl;
    return a.exec();
}
