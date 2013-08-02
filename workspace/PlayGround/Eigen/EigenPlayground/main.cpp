#include <eigen3/Eigen/Eigen>
#include <iostream>

using namespace Eigen;
int main()
{
    VectorXd xD(7);
    xD << 1,2,3,4,5,6,9;
    std::cout << xD.rows() << std::endl;
    Vector3d v;
    v[0]=0;
    v[1]=1;
    v[2]=9;
    std::cout << v<< std::endl;
    return 0;
}
