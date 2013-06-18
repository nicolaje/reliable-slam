#ifndef SUBPAVING_H
#define SUBPAVING_H
#include <ibex.h>
#include <vector>

class SubPaving
{
public:
    SubPaving();
    /**
     * @brief ImageSP: implementation of ImageSP algorithm
     * @param boxList: list to be merged as a set of non-overlapping boxes (subpaving)
     * @return a subpaving
     */
    static SubPaving ImageSP(std::vector<ibex::IntervalVector> boxList);
private:
    SubPaving *left;
    SubPaving *right;
    ibex::IntervalVector box();
};

#endif // SUBPAVING_H
