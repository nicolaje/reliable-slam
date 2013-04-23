//chdir(fullpath('../../Simulations/Scenarios/2D-2Transponders'))
cd /media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Simulations/Scenarios/2D-2Transponders

raw_file=read_csv('2D-2Transponders.res',';');

// avoid the first comment line + parse strings to double
data=evstr(raw_file(2:size(raw_file,1),:));

// The generalized State Vector is:
//  1  2   3      4    5    6    7   # index
// [x, y, theta, xl1, yl1, xl2, yl2]

// Fx (to map the 3D state vector of the robot to the 2N+3 D generalized 
// state vector)
// Here we have 2 landmarks so the vector is of dimension 7
Fx=[eye(3,3) zeros(3,4)];

// Covariance of the motion noise
Mt=[1 0;
    0 1];
    
// Covariance of the range sensor
Cr=1;
// Covariance of the heading sensor
Ch=1;

// Adapted from "Preliminary results in Range-Only Localization and Mapping"
// returns the estimated relative displacement between each landmark and the robot
// and the estimated covariance: a "linearized" annular distribution
// from the range measurement and the previously estimated state vector
function [z1, z2, C1, C2]=range_only_measurement(rm1,rm2,x,sigma)
    theta1=atan((x(2)-x(5))/(x(1)-x(4));
    theta2=atan((x(2)-x(7))/(x(1)-x(6));
    z1=[x(4);x(5)]+rm1*[cos(theta1);sin(theta1)];
    z2=[x(6);x(7)]+rm2*[cos(theta2);sin(theta2)];
    PHI1=[cos(theta1) -sin(theta1);
            sin(theta1) cos(theta1)];
    PHI2=[cos(theta2) -sin(theta2);
            sin(theta2) cos(theta2)];
    C1=PHI1*[sigma 0;
                0 10*sigma]*PHI1';
    C2=PHI2*[sigma 0;
                0 10*sigma]*PHI2';
endfunction

// The EKF SLAM algorithm with known correspondences landmarks
// We give r1t, r2t, theta as inputs instead of zi because
// we reconstruct the zi ourselves from the range readings
function [mut, sigmat]=EKF_SLAM(mut_prev, sigmat_prev, ut, r1t, r2t, theta, dt)

      ////////////////
     // PREDICTION //
    ////////////////
    mut=mut_prev+Fx'*[ut(1)*dt*cos(mut_prev(3));
                        ut(1)*dt*sin(mut_prev(3));
                        dt*ut(2)];
    Gt=eye(7,7)+Fx'*[0 0 -ut(1)*dt*sin(mut_prev(3));
                        0 0 ut(1)*dt*cos(mut_prev(3));
                        0 0 0]*Fx;
    
    // Jacobian of the motion model
    // with respect to the motion parameters
    Vt=[dt*cos(mut_prev(3)) 0;
        dt*sin(mut_prev(3)) 0;
        0 dt];

    // Covariance of the motion noise
    // mapped in the state space
    Rt=Vt*Mt*Vt';
                        
    sigmat=Gt*sigmat_prev*Gt'+Fx'*Rt*Fx;
    
      ////////////
     // UPDATE //
    ////////////
    
    // expected measurements
    z1hat=[mut(1)-mut(4) ;
           mut(2)-mut(5)];
    z2hat=[mut(1)-mut(6) ;
           mut(2)-mut(7)];
    thetaHat=mut(3);
    
    [z1t,z2t,C1,C2]=range_only_measurements(r1t,r2t,mut_prev,Cr);
    
    // Only with measurement 1 and heading first
    Ct1=[1 0 0 -1 0 0 0;
         0 1 0 0 -1 0 0;
         0 0 1 0 0 0 0;
        -1 0 0 1 0 0 0;
         0 -1 0 0 1 0 0;
         0 0 0 0 0 0 0;
         0 0 0 0 0 0 0];
        
    Qt1=[C1 0;
         0 0 Ch];
    
    // Kalman gain
    Kt1=sigmat*Ct1'*inv(Ct1*sigmat*Ct1'+Qt1);
    mut=mut+Kt1*([z1t; theta)]-[z1hat; thetaHat]);
    
    // Update the covariance of the state
    sigmat=(eye(3,3)-Kt1*Ct1)*sigmat;
    
    // Measurement 2
    Ct2=[1 0 0 -1 0 0 0;
         0 1 0 0 -1 0 0;
         0 0 0 0 0 0 0;
         0 0 0 0 0 0 0;
         0 0 0 0 0 0 0;
        -1 0 0 0 0 1 0;
         0 -1 0 0 0 0 1];
    Qt2=C2;
    
    Kt2=sigma*Ct2'*inv(Ct2*sigmat*Ct2'+Qt2);
    mut=mut+Kt2*([z2t]-[z2hat]);
    sigmat=(eye(3,3)-Kt2*Ct2)*sigmat;
endfunction


  //////////////////
 // Main Program //
//////////////////