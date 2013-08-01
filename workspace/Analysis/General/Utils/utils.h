#ifndef UTILS_H
#include <ibex/ibex.h>
#include <eigen3/Eigen/Eigen>
#define UTILS_H

class Utils
{
public:
    static ibex::IntervalVector eigenVectorToIntervalVector(Eigen::VectorXd vector);
};

#endif // UTILS_H
