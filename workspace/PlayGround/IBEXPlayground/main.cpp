#include <QApplication>
#include <ibex/ibex.h>

using namespace ibex;

int main(int argc, char *argv[])
{
    IntervalVector v1(2),v2(2);
    v1[0]=1;
    std::cout << v1.is_superset(v2)<<std::endl;
}
