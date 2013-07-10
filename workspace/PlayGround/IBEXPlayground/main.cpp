#include <QApplication>
#include "mainwindow.h"
#include <ibex.h>
using namespace ibex;
int main(int argc, char *argv[])
{
    System sys("system.txt");
    Function f=sys.f;
    IntervalVector vec(4);
    CtcFwdBwd ctc(f);
    CtcFixPoint fix(ctc);
    fix.contract(vec);
    ctc.contract(vec);
//    std::cout << vec << std::endl;
    System sys2("/home/jem/reliable-slam/workspace/Analysis/IntervalAnalysis/BoundedErrorEstimatorSLAM-build-desktop-Qt_4_8_2_in_PATH__System__Release/ObservationModelSystem.txt");
}
