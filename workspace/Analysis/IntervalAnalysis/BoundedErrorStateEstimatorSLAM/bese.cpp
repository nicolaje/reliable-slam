#include "bese.h"
#include "QDebug"
using namespace ibex;
BESE::BESE(IntervalVector initState, int nbRobots, int nbLandmarks, bool useSubPavings)
{
    this->state=new IntervalVector(initState);
    this->nbLandmarks=nbLandmarks;
    this->nbRobots=nbRobots;
    this->useSubPavings=useSubPavings;

    this->fPrime=new Function("f_prime.txt");

    // TODO: ask G.C. :
    // Function motion=*motionModel;
    // I don't know why we can't directly use *motionModel in a NumConstraint

    this->motionModel=new Function("MotionModel.txt");
//    System sys("ObservationModelSystem.txt");
//    (*observationModel)=sys.f; //=new Function(ObservationModel.txt");

    this->motionModelByContractor=new Function("MotionModelByContractor.txt");
    this->motionContractor=new CtcFwdBwd(*this->motionModelByContractor);
    this->motionFixPointContractor=new CtcFixPoint(*this->motionContractor);

    this->sensorsModelByContractor=new Function("SensorsModelByContractor.txt");
    this->sensorsContractor=new CtcFwdBwd(*this->sensorsModelByContractor);
    this->sensorsFixPointContractor=new CtcFixPoint(*this->sensorsContractor);
}

void BESE::predictByContractor(IntervalVector vector, Interval dt)
{
}

void BESE::predict(Interval dt)
{
    IntervalVector v(9);
    for(int i=0; i<9; i++){
        v[i]=(*measurements)[i];
    }
    (*state)+=dt*(*fPrime).eval_vector(v);
}

void BESE::update(IntervalVector *vector)
{
    // For now we cheat, and don't
    // predict/update on the orientation
//    (*this->state)[2]=(*vector)[0]; // Pressure sensor

    for(int i=0; i<3; i++){
        (*this->state)[3+i]=(*vector)[1+i];
    }
//    IntervalVector dist(nbLandmarks);
//    for(int i=0;i<nbLandmarks;i++)
//        dist[i]=(*vector)[1+3+i];
//    Function f=makeObservationModel((*vector));//dist);
//    CtcFwdBwd ctc(f);
//    CtcFixPoint fix(ctc,0.001);
    System sys("ObservationModelSystem.txt");
    CtcFwdBwd out1(sys.f,LT);//*observationModel,LT);
    CtcFwdBwd out2(sys.f,GT);//*observationModel,GT);
    CtcCompo out(out1,out2);
    CtcFixPoint outFix(out,0.001);

    IntervalVector extState((*state).size()+(*vector).size());
    for(int i=0;i<(*state).size();i++){
        extState[i]=(*state)[i];
    }
    for(int i=0;i<(*vector).size();i++){
        extState[(*state).size()+i]=(*vector)[i];
    }
    CtcFwdBwd ctc(sys.f);//*observationModel);
    CtcFixPoint fix(ctc,0.001);
    try{
        fix.contract(extState);
        outFix.contract(extState);
//        fix.contract((*state));
//        if(stateBack!=(*state)){
//            IntervalVector *v;
//            std::cout << "Inner contraction useful" << std::endl;
//            std::cout << stateBack.diff((*state),v) << std::endl;
//        }
//        out.contract((*state));
//        if(stateBack!=(*state))
//            std::cout << "Outer contraction useful" << std::endl;
    }catch(EmptyBoxException e){
        std::cout << "Empty box!!" << std::endl;
        std::cout << "ExtState: " << extState << std::endl;
        std::cout << "State: " << (*state) << std::endl;
    }
    for(int i=0;i<(*state).size();i++){
        (*state)[i]=extState[i];
    }

//    Variable a,b(2);
//    Function f(a,b,Return(a,a)+b);
//    Function fu(v,o,(*observationModel)(v)-o);
//    NumConstraint c((*observationModel)=0);//=*vector);
//    CtcFwdBwd ctc(fu);
//    CtcFixPoint fixPoint(ctc,0.01);
//    IntervalVector bigVect(state->size()+3+getLandmarkNB());
//    for(int i=0; i<state->size(); i++){
//        bigVect[i]=(*state)[i];
//    }
//    for(int i=0; i<3+getLandmarkNB(); i++){
//        bigVect[state->size()+i]=(*vector)[i];
//    }
//    fixPoint.contract(bigVect);
}

void BESE::updateData(Robot robot)
{
    this->measurements=robot.getObservationsAsIntervalVector();
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

Function BESE::makeObservationModel(IntervalVector obs)
{
    Variable x[18];
    Array<const ExprSymbol> vars(18);
    for(int i=0; i<18;i++)
        vars.set_ref(i,x[i]);
    Function f(vars,Return(//obs[0],
                           //obs[1],
                           //obs[2],
                           //obs[3],
                           sqrt(sqr(x[0]-x[6])+sqr(x[1]-x[7])+sqr(x[2]-x[8]))-obs[4],
                           sqrt(sqr(x[0]-x[9])+sqr(x[1]-x[10])+sqr(x[2]-x[11]))-obs[5],
                           sqrt(sqr(x[0]-x[12])+sqr(x[1]-x[13])+sqr(x[2]-x[14]))-obs[6],
                           sqrt(sqr(x[0]-x[15])+sqr(x[1]-x[16])+sqr(x[2]-x[17]))-obs[7]));
    return f;
}

IntervalVector BESE::getOrientation()
{
    IntervalVector res(3);
    for(int i=0; i<3; i++){
        res[i]=(*this->state)[3+i];
    }
    return res;
}

int BESE::getLandmarkNB()
{
    return this->nbLandmarks;
}

int BESE::getRobotNB()
{
    return this->nbRobots;
}
