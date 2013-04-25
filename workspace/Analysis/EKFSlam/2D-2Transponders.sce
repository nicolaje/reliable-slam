cd /media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Simulations/Scenarios/2D-2Transponders

raw_file=read_csv('2D-2Transponders.res',';');

// avoid the first comment line + parse strings to double
data=evstr(raw_file(2:size(raw_file,1),:));

// The generalized State Vector is:
//  1  2   3      4    5    6    7   # index
// [x, y, theta, xl1, yl1, xl2, yl2]

// Covariance of the heading sensor
Ch=1;

// Covariance of the motion noise
Mt=[1 0 0;
0 1 0;
0 0 Ch];

// Covariance of the range sensor
Cr=1;

// Observation matrix:

C=[0 0 1 0 0 0 0; // Compass
1 0 0 -1 0 0 0; // Landmark 1 on x-axis
0 1 0 0 -1 0 0; // Landmark 1 on y-axis
1 0 0 0 0 -1 0; // Landmark 2 on x-axis
0 1 0 0 0 0 -1] // Landmark 2 on y-axis


// Adapted from "Preliminary results in Range-Only Localization and Mapping"
// returns the sensors reading stacked into a vector and their covariance matrix
// with the estimated relative displacement between each landmark and the robot
// y_partial=[theta; r1; r2]
function [y, W]=range_only_measurement(y_partial,x)
    theta1=atan((x(2)-x(5))/(x(1)-x(4));
    theta2=atan((x(2)-x(7))/(x(1)-x(6));

    z1=rm1*[cos(theta1);sin(theta1)];
    z2=rm2*[cos(theta2);sin(theta2)];
    PHI1=[cos(theta1) -sin(theta1);
    sin(theta1) cos(theta1)];

    PHI2=[cos(theta2) -sin(theta2);
    sin(theta2) cos(theta2)];

    C1=PHI1*[sigma 0;
    0 10*sigma]*PHI1';

    C2=PHI2*[sigma 0;
    0 10*sigma]*PHI2';

    y=[theta;
    z1;
    z2]

    W=[Ch 0 0 0 0;
    0 C1 0 0;
    0 0 0 C2];
endfunction

// The EKF SLAM algorithm with known correspondences landmarks
// We give r1t, r2t, theta as inputs instead of zi because
// we reconstruct the zi ourselves from the range readings
function [mut, sigmat]=EKF_SLAM(mut_prev, sigmat_prev, ut, y_partial, dt)

    ////////////////
    // PREDICTION //
    ////////////////

    // Fx (to map the 3D state vector of the robot to the 2N+3 D generalized 
    // state vector)
    // Here we have 2 landmarks so the vector is of dimension 7
    Fx=[eye(3,3) zeros(3,4)];
    
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

    // Build the estimated full observation
    [y,W]=range_only_measurement(y_partial,mut);

    delta_y=y-H*mut;
    S=H*sigmat*H'+W;
    R=sigmat*H*inv(S);

    mut=mut+R*delta_y; // Update the state vector
    sigmat=sigmat-R*H*sigmat; // Update the covariance
endfunction

// Function to draw a confidence ellipse (from Luc Jaulin's scripts)
function Draw_Ellipse(what,G_w,eta,couleur,thick);  //eta-confidence ellipse
    xset('thickness',thick);                         // The ellipse encloses the random vector
    s=0:0.05:2*%pi+0.05;                             // with a probability eta
    w=what*ones(s)+sqrtm(-2*log(1-eta)*G_w)*[cos(s);sin(s)];
    xset("color",couleur);
    xpoly(w(1,:),w(2,:));
endfunction

//////////////////
// Main Program //
//////////////////

// Estimate of the original state
x=[0,0,0,0,0,0,0];

// Original covariance
sigma=50*eye(7,7);
dt=1;
for i=1:1:10,
    
end