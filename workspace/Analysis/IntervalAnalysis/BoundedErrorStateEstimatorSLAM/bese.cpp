#include "bese.h"
#include "QDebug"
using namespace ibex;
BESE::BESE(IntervalVector initState, int nbRobots, int nbLandmarks, bool useSubPavings)
{
    this->state=new IntervalVector(initState);
    this->nbLandmarks=nbLandmarks;
    this->nbRobots=nbRobots;
    this->useSubPavings=useSubPavings;
    this->euler=new Function("euler.txt");
}

void BESE::predict(Interval dt)
{
    IntervalVector v(3);
    IntervalVector ori(3);
    IntervalVector x(3);
    for(int i=0;i<3;i++){
        x[i]=(*state)[i];
        v[i]=(*measurements)[6+i]; // CP linear speed in v
        ori[i]=(*measurements)[3+i]; // (*state)[i]; // cp orientation
    }
    x+=dt*(*euler).eval_matrix(ori)*v;
    for(int i=0;i<3;i++)
        (*state)[i]=x[i]; // Update the position of the robot
}

void BESE::update(IntervalVector vector)
{
    this->measurements=&vector;
    for(int i=0; i<3; i++){
        (*this->state)[3+i]=vector[3+i]; // Update orientation
    }
    System sys("ObservationModelSystem.txt");
    CtcFwdBwd out1(sys.f,LT);
    CtcFwdBwd out2(sys.f,GT);
    CtcCompo out(out1,out2);
    CtcFixPoint outFix(out,0.001);

    IntervalVector extState((*state).size()+vector.size());
    for(int i=0;i<(*state).size();i++){
        extState[i]=(*state)[i];
    }
    for(int i=0;i<vector.size();i++){
        extState[(*state).size()+i]=vector[i];
    }
    CtcFwdBwd ctc(sys.f);
    CtcFixPoint fix(ctc);
    try{
        fix.contract(extState);
        outFix.contract(extState);
    }catch(EmptyBoxException e){
        std::cout << "Empty box!!" << std::endl;
        std::cout << "ExtState: " << extState << std::endl;
        std::cout << "State: " << (*state) << std::endl;
    }
    for(int i=0;i<(*state).size();i++){
        (*state)[i]=extState[i];
    }
}

IntervalVector BESE::getPosition()
{
    IntervalVector res(3);
    for(int i=0; i<3; i++){
        res[i]=(*this->state)[i];
    }
    return res;
}

std::string BESE::toString()
{
    std::string res;
    std::ostringstream ss;
    for(int i=0; i<(*state).size(); i++){
        ss << (*state)[i].lb() <<";"<<(*state)[i].ub()<<";";
    }
    res=ss.str();
    return res+"\n";
}

std::string BESE::debugToString()
{
    std::string res;
    std::ostringstream ss;
    for(int i=0; i<(*state).size(); i++){
        ss << (*state)[i].lb() <<";"<<(*state)[i].ub()<<";\n";
    }
    res=ss.str();
    return res+"\n";
}

IntervalVector BESE::getOrientation()
{
    IntervalVector res(3);
    for(int i=0; i<3; i++){
        res[i]=(*this->state)[3+i];
    }
    return res;
}

IntervalVector BESE::getMap()
{
    IntervalVector map(this->getLandmarkNB()*3);
    for(int i=0;i<this->getLandmarkNB()*3;i++){
        map[i]=(*this->state)[6+i];
    }
    return map;
}

int BESE::getLandmarkNB()
{
    return this->nbLandmarks;
}

int BESE::getRobotNB()
{
    return this->nbRobots;
}
