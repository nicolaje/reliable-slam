#include <eigen3/Eigen/Eigen>
#include <iostream>

using namespace Eigen;
int main()
{
    VectorXd xD(7);
    xD << 1,2,3,4,5,6,9;
    std::cout << xD.rows() << std::endl;
    return 0;
}
