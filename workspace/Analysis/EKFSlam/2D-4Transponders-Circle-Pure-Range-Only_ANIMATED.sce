cd /media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Simulations/Scenarios/2D-4Transponders

clear
close
close
close
funcprot(0);

raw_file=read_csv('2D-4Transponders-Circle.res',';');

// Degrees to radians
deg2rad=%pi/180;

// avoid the first comment line + parse strings to double
data=evstr(raw_file(2:size(raw_file,1),:));

// Variance of the heading sensor
Ch=(0.2*deg2rad)^2;

// Covariance of the motion noise
Mt=[0.04^2 0;
0 (0.01*deg2rad)^2];

// Variance of the range sensor
Cr=0.03^2;

// The EKF SLAM algorithm with known correspondences landmarks
function [mut, sigmat]=EKF_SLAM(mut_prev, sigmat_prev, ut, y, dt)

    //////////////////
    // PREDICTION ///
    ////////////////

    // Fx (to map the 3D state vector of the robot to the 2N+3 D generalized 
    // state vector)
    // Here we have 4 landmarks so the vector is of dimension 11
    Fx=[eye(3,3) zeros(3,8)];

    mut=mut_prev+Fx'*[ut(1)*dt*cos(mut_prev(3));
    ut(1)*dt*sin(mut_prev(3));
    dt*ut(2)];

    Gt=eye(11,11)+Fx'*[0 0 -ut(1)*dt*sin(mut_prev(3));
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

    //////////////
    // UPDATE ///
    ////////////

    // Jacobian of the observation matrix
    C=[0 0 1 0 0 0 0 0 0 0 0;
    (mut(1)-mut(4))/y(2) (mut(2)-mut(5))/y(2) 0 (mut(4)-mut(1))/y(2) (mut(5)-mut(2))/y(2) 0 0 0 0 0 0;
    (mut(1)-mut(6))/y(3) (mut(2)-mut(7))/y(3) 0 0 0 (mut(6)-mut(1))/y(3) (mut(7)-mut(2))/y(3) 0 0 0 0;
    (mut(1)-mut(8))/y(4) (mut(2)-mut(9))/y(4) 0 0 0 0 0 (mut(8)-mut(1))/y(4) (mut(9)-mut(2))/y(4) 0 0;
    (mut(1)-mut(10))/y(5) (mut(2)-mut(11))/y(5) 0 0 0 0 0 0 0 (mut(10)-mut(1))/y(5) (mut(11)-mut(2))/y(5)];

    W=[Ch zeros(1,4);
    zeros(4,1) Cr*eye(4,4)];

    delta_y=y-C*mut;
    S=C*sigmat*C'+W;
    R=sigmat*C'*inv(S);

     mut=mut+R*delta_y; // Update the state vector
     sigmat=sigmat-R*C*sigmat; // Update the covariance
endfunction

// Function to draw a confidence ellipse (from Luc Jaulin's scripts)
function Draw_Ellipse(what,G_w,eta,thick,c);  //eta-confidence ellipse
    xset('thickness',thick);                         // The ellipse encloses the random vector
    xset('color',c);
    s=0:0.05:2*%pi+0.05;                             // with a probability eta
    w=what*ones(s)+sqrtm(-2*log(1-eta)*G_w)*[cos(s);sin(s)];
    xpoly(w(1,:),w(2,:));
endfunction

function Draw_True_Path(x,len);
    xset('color',1);
    xset('thickness',1);
    if size(x,1)<len then // if the history is not big enough
        len=size(x,1); 
    end
    real_length=size(x,1);
    plot(x(real_length-1:))
endfunction

////////////////////
// Main Program ///
//////////////////

// Data Format
// 1            2            3            4             5             6             7              8
// pose_pure.x; pose_pure.y; pose_pure.z; pose_noisy.x; pose_noisy.y; pose_noisy.z; pose_pure.yaw; pose_pure.pitch;
// 9               10              11                12               13            14            15
// pose_pure.roll; pose_noisy.yaw; pose_noisy.pitch; pose_noisy.roll; imu_pure.d²x; imu_pure.d²y; imu_pure.d²z;
// 16             17             18             19               20             21             22
// imu_noisy.d²x; imu_noisy.d²y; imu_noisy.d²z; imu_pure.dtheta; imu_pure.dphi; imu_pure.dpsi; imu_noisy.dtheta;
// 23              24             
// imu_noisy.dphi; imu_noisy.dpsi;
// 25                    26                    27                    28                     29                     30
// loch_doppler_pure.vx; loch_doppler_pure.vy; loch_doppler_pure.vz; loch_doppler_noisy.vx; loch_doppler_noisy.vy; loch_doppler_noisy.vz;
// 31                 32                 33                 34
// transponder1_pure; transponder2_pure; transponder3_pure; transponder4_pure; 
// 35                  36                  37                  38
// transponder1_noisy; transponder1_noisy; transponder1_noisy; transponder1_noisy;

// The generalized State Vector is:
//  1  2   3      4    5    6    7   # index
// [x, y, theta, xl1, yl1, xl2, yl2, xl3, yl3, xl4, yl4]

// Estimate of the original state
//x=[data(1,1); data(1,2); 0; 20; 0; -20; 0; 0; 20; 0; -20];
x=[data(1,1); data(1,2); data(1,7); 20; 0; -20; 0; 0; 20; 0; -20];

// Original covariance
sigma=[zeros(3,11);
zeros(8,3) 15*15*eye(8,8)];

dt=1;
x_stack=[];
x_prev_stack=x;
u_stack=[];
y_stack=[];
for i=1:1:size(data,1),
    x_stack=[x_stack [data(i,1); data(i,2); data(i,7); 20; 0; -20; 0; 0; 20; 0; -20]];
    y=[data(i, 7); data(i, 31); data(i, 32); data(i, 33); data(i,34)];
    ut=[data(i,25); 2*%pi/120]; //data(i,21)];
    [x,sigma]=EKF_SLAM(x,sigma,ut,y,dt);
    x_prev_stack=[x_prev_stack x];
    u_stack=[u_stack ut];
    y_stack=[y_stack y];
end