#include <eigen3/Eigen/Eigen>
#include <iostream>

using namespace Eigen;
int main()
{
    MatrixXd m(2,2);
    m(0,0)=0;
    m(0,1)=1;
    m(1,0)=2;
    m(1,1)=3;
    std::cout << m << std::endl;
    return 0;
}
