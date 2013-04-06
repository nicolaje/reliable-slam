#include "sivia.h"
#include <qdebug.h>
static double v_bar=1;

void Sivia::contract_and_draw(Ctc& c, IntervalVector& box, const QColor & pencolor, const QColor & brushcolor) {
    IntervalVector initbox=box;       // get a copy
    try {
        c.contract(box);
        if (box==initbox) return;     // nothing contracted.
        IntervalVector* rest;
        int n=initbox.diff(box,rest); // calculate the set difference
        for (int i=0; i<n; i++) {     // display the boxes
            frame.DrawBox(rest[i][0],rest[i][1],QPen(pencolor),QBrush(brushcolor));
        }
        delete[] rest;
    } catch(EmptyBoxException&) {
        frame.DrawBox(initbox[0],initbox[1],QPen(pencolor),QBrush(brushcolor));
    }
}

Sivia::Sivia(Frame& frame, double epsilon) : frame(frame) {

    // Create the function we want to apply SIVIA on.
    Variable x1,x2,a1,a2;

    Function f_sup("f_sup.txt");
    Function f_inf("f_inf.txt");
    Function V("V.txt");
    Function dV("gradV.txt");

    NumConstraint c1_c(x1,x2,a1,a2,a1*dV(x1,x2)[0]+a2*dV(x1,x2)[1]>=0);

    NumConstraint c21_c(x1,x2,a1,a2,f_sup(x1,x2)[0]-a1>=0);
    NumConstraint c22_c(x1,x2,a1,a2,f_sup(x1,x2)[1]-a2>=0);

    NumConstraint c31_c(x1,x2,a1,a2,a1-f_inf(x1,x2)[0]>=0);
    NumConstraint c32_c(x1,x2,a1,a2,a2-f_inf(x1,x2)[1]>=0);

    NumConstraint c41_c(x1,x2,V(x1,x2)>=0);
    NumConstraint c42_c(x1,x2,V(x1,x2)<=v_bar);

    CtcFwdBwd c1(c1_c);

    CtcFwdBwd c21(c21_c);
    CtcFwdBwd c22(c22_c);
    CtcCompo c2(c21,c22);

    CtcFwdBwd c31(c31_c);
    CtcFwdBwd c32(c32_c);
    CtcCompo c3(c31, c32);

    CtcFwdBwd c41(c41_c);
    CtcFwdBwd c42(c42_c);
    CtcCompo c4(c41,c42);

    CtcCompo cOut1(c1,c2);
    CtcCompo cOut2(c3,c4);

    CtcCompo cOut(cOut1,cOut2);

    NumConstraint c1_cIn(x1,x2,a1,a2,a1*dV(x1,x2)[0]+a2*dV(x1,x2)[1]>=0);

    NumConstraint c21_cIn(x1,x2,a1,a2,f_sup(x1,x2)[0]-a1<0);
    NumConstraint c22_cIn(x1,x2,a1,a2,f_sup(x1,x2)[1]-a2<0);

    NumConstraint c31_cIn(x1,x2,a1,a2,a1-f_inf(x1,x2)[0]<0);
    NumConstraint c32_cIn(x1,x2,a1,a2,a2-f_inf(x1,x2)[1]<0);

    NumConstraint c41_cIn(x1,x2,V(x1,x2)<0);
    NumConstraint c42_cIn(x1,x2,V(x1,x2)>v_bar);

    CtcFwdBwd c1_In(c1_cIn);

    CtcFwdBwd c21_In(c21_cIn);
    CtcFwdBwd c22_In(c22_cIn);
    CtcUnion c2_In(c21_In, c22_In);

    CtcFwdBwd c31_In(c31_cIn);
    CtcFwdBwd c32_In(c32_cIn);
    CtcUnion c3_In(c31_In, c32_In);

    CtcFwdBwd c41_In(c41_cIn);
    CtcFwdBwd c42_In(c42_cIn);
    CtcUnion c4_In(c41_In, c42_In);

    CtcUnion cIn1(c1_In, c2_In);
    CtcUnion cIn2(c3_In, c4_In);

    CtcUnion cIn(cIn1, cIn2);

    // Build the initial box.
    IntervalVector box(4);
    box[0]=Interval(-10,10);
    box[1]=Interval(-10,10);
    box[2]=Interval::ALL_REALS;
    box[3]=Interval::ALL_REALS;

    // Build the way boxes will be bisected.
    // "LargestFirst" means that the dimension bisected
    // is always the largest one.
    LargestFirst lf;

    stack<IntervalVector> s;
    s.push(box);

    while (!s.empty()) {
        // Get a copy of the current box (on top of the stack)
        IntervalVector box=s.top();


//        qDebug() << "a[0]= [" <<box[2].lb() << "; " << box[2].ub() << "], a[1]= [" << box[3].lb() << "; " <<box[3].ub() << "]" << endl;
        // Remove the box from the stack
        s.pop();
        try {
            // Remove the part that is outside
            contract_and_draw(cIn,box,Qt::magenta,Qt::red);
            if (box.is_empty()) { continue; }

            // Remove the part that is inside
            contract_and_draw(cOut,box,Qt::darkBlue,Qt::cyan);
            if (box.is_empty()) { continue; }

            // Check if the box is small enough
            if (box.max_diam()<epsilon) {
                frame.DrawBox(box[0],box[1],QPen(Qt::yellow),QBrush(Qt::yellow));
            } else {
                // otherwise, bisect it and
                // push the two subboxes on the stack.
                pair<IntervalVector,IntervalVector> boxes=lf.bisect(box);
                s.push(boxes.first);
                s.push(boxes.second);
            }
        } catch(EmptyBoxException&) { }
    }


    frame.Save("paving");
}
