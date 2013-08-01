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
