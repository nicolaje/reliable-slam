bool isVStable(double epsilon){
    // Create the function we want to apply SIVIA on.
    Variable x1,x2;
    Function f_sup("f_sup.txt");
    Function f_inf("f_inf.txt");
    Function V("V.txt");
    Function dV("gradV.txt");
    Function min_(x1,x2,ibex::min(x1,x2));

    NumConstraint c1_out(x1,x2,min_(dV(x1,x2)[0],dV(x1,x2)[1])*10>=0);
    NumConstraint c1_in(x1,x2,min_(dV(x1,x2)[0],dV(x1,x2)[1])*10<0);
    NumConstraint c2_out(x1,x2,min_(f_sup(x1,x2)[0],f_sup(x1,x2)[1])>=10);
    NumConstraint c2_in(x1,x2,min_(f_sup(x1,x2)[0],f_sup(x1,x2)[1])<10);
    NumConstraint c3_out(x1,x2,min_(f_inf(x1,x2)[0],f_inf(x1,x2)[1])<=10);
    NumConstraint c3_in(x1,x2,min_(f_inf(x1,x2)[0],f_inf(x1,x2)[1])>10);
    NumConstraint c4_out1(x1,x2,V(x1,x2)>=0);
    NumConstraint c4_out2(x1,x2,V(x1,x2)<=v_bar);
    NumConstraint c4_in1(x1,x2,V(x1,x2)<0);
    NumConstraint c4_in2(x1,x2,V(x1,x2)>v_bar);

   // Create contractors with respect to each of the previous constraints.
    CtcFwdBwd out1(c1_out);
    CtcFwdBwd in1(c1_in);
    CtcFwdBwd out2(c2_out);
    CtcFwdBwd in2(c2_in);
    CtcFwdBwd out3(c3_out);
    CtcFwdBwd in3(c3_in);
    CtcFwdBwd out41(c4_out1);
    CtcFwdBwd in41(c4_in1);
    CtcFwdBwd out42(c4_out2);
    CtcFwdBwd in42(c4_in2);
    CtcUnion in4(in41,in42);
    CtcCompo out4(out41,out42);

    // Create a contractor that removes all the points
    // that do not satisfy either f(x,y)<=2 or f(x,y)>=0.
    // These points are "outside" of the solution set.
    CtcCompo out5(out1,out2);
    CtcCompo out6(out3,out4);
    CtcCompo out(out5,out6);

    // Create a contractor that removes all the points
    // that do not satisfy both f(x,y)>2 or f(x,y)<0.
    // These points are "inside" the solution set.
    CtcUnion in5(in1,in2);
    CtcUnion in6(in3,in4);
    CtcUnion in(in5,in6);

    // Build the initial box.
    IntervalVector box(2);
    box[0]=Interval(-10,10);
    box[1]=Interval(-10,10);

    // Build the way boxes will be bisected.
    // "LargestFirst" means that the dimension bisected
    // is always the largest one.
    LargestFirst lf;

    stack<IntervalVector> s;
    s.push(box);

    while (!s.empty()) {
        // Get a copy of the current box (on top of the stack)
        IntervalVector box=s.top();

        // Remove the box from the stack
        s.pop();
        try {
            // Remove the part that is outside
            contract_and_draw(in,box,Qt::magenta,Qt::red);
            if (box.is_empty()) { continue; }

            // Remove the part that is inside
            contract_and_draw(out,box,Qt::darkBlue,Qt::cyan);
            if (box.is_empty()) { continue; }

            // Check if the box is small enough
            if (box.max_diam()<epsilon) {
                frame.DrawBox(box[0],box[1],QPen(Qt::yellow),QBrush(Qt::NoBrush));
            } else {
                // otherwise, bisect it and
                // push the two subboxes on the stack.
                pair<IntervalVector,IntervalVector> boxes=lf.bisect(box);
                s.push(boxes.first);
                s.push(boxes.second);
            }
        } catch(EmptyBoxException&) {
        }
    }
}

bool hasSolution(Ctc& c, IntervalVector& box){
    IntervalVector initbox=box;       // get a copy
    try {
        c.contract(box);
        if (box==initbox) return false;     // nothing contracted.
        IntervalVector* rest;
        int n=initbox.diff(box,rest); // calculate the set difference
//        for (int i=0; i<n; i++) {     // display the boxes
//            frame.DrawBox(rest[i][0],rest[i][1],QPen(pencolor),QBrush(brushcolor));
//        }
        return true;
        delete[] rest;
    } catch(EmptyBoxException&) {
//        frame.DrawBox(initbox[0],initbox[1],QPen(pencolor),QBrush(brushcolor));
        return false;
    }
}
