#include "utils.h"
using namespace Eigen;
using namespace ibex;

IntervalVector Utils::eigenVectorToIntervalVector(VectorXd vector)
{
    IntervalVector res(vector.rows());
    for(int i=0;i<vector.rows();i++)
        res[i]=vector[i];
    return res;
}

VectorXd Utils::intervalVectorToEigenVector(IntervalVector vector)
{
    VectorXd res(vector.size());
    for(int i=0;i<res.rows();i++)
        res[i]=vector[i].mid();
    return res;
}

MatrixXd Utils::boxToCovarianceMatrix(IntervalVector box, int confidence)
{
    MatrixXd mat(box.size(),box.size());
    for(int i=0,j=0;i<box.size(),j<box.size();i++,j++)
        mat(i,j)=(i==j?pow(box[i].mid()/confidence,2):0);
    return mat;
}
