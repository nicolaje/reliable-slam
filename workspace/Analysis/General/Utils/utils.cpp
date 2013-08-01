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
