cd /media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Simulations/Scenarios/2D-2Transponders

clear
close
close
close
funcprot(0);

raw_file=read_csv('2D-2Transponders-Line.res',';');

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

    // Jacobian of the observation matrix
    C=[0 0 1 0 0 0 0;
    (mut(1)-mut(4))/y(2) (mut(2)-mut(5))/y(2) 0 (mut(4)-mut(1))/y(2) (mut(5)-mut(2))/y(2) 0 0;
    (mut(1)-mut(6))/y(3) (mut(2)-mut(7))/y(3) 0 0 0 (mut(6)-mut(1))/y(3) (mut(7)-mut(2))/y(3)];

    W=[Ch zeros(1,2);
    zeros(2,1) Cr*eye(2,2)];

    delta_y=y-C*mut;
    S=C*sigmat*C'+W;
    R=sigmat*C'*inv(S);

    mut=mut+R*delta_y; // Update the state vector
    sigmat=sigmat-R*C*sigmat; // Update the covariance
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

// Data Format
// 1            2            3            4             5             6             7              8
// pose_pure.x; pose_pure.y; pose_pure.z; pose_noisy.x; pose_noisy.y; pose_noisy.z; pose_pure.yaw; pose_pure.pitch;
// 9               10              11                12               13            14            15
// pose_pure.roll; pose_noisy.yaw; pose_noisy.pitch; pose_noisy.roll; imu_pure.d²x; imu_pure.d²y; imu_pure.d²z;
// 16             17             18             19               20             21             22
// imu_noisy.d²x; imu_noisy.d²y; imu_noisy.d²z; imu_pure.dtheta; imu_pure.dphi; imu_pure.dpsi; imu_noisy.dtheta;
// 23              24              25                 26                 27                  28
// imu_noisy.dphi; imu_noisy.dpsi; transponder1.pure; transponder2.pure; transponder1.noisy; transponder2.noisy;
// 29                    30                    31                    32                     33                     34
// loch_doppler_pure.vx; loch_doppler_pure.vy; loch_doppler_pure.vz; loch_doppler_noisy.vx; loch_doppler_noisy.vy; loch_doppler_noisy.vz;

// The generalized State Vector is:
//  1  2   3      4    5    6    7   # index
// [x, y, theta, xl1, yl1, xl2, yl2]

// Estimate of the original state
x=[0; -30; 0; 20; 0; -20; 0];

// Original covariance
sigma=[zeros(3,7);
zeros(4,3) 20*eye(4,4)];

dt=1;
x_stack=[];
x_prev_stack=x;
u_stack=[];
y_stack=[];
for i=1:1:size(data,1),
    x_stack=[x_stack [data(i,1); data(i,2); data(i,7); 20; 0; -20; 0]];
    y=[data(i, 10); data(i, 27); data(i, 28)];
    ut=[data(i,32); data(i,24)];
    [x,sigma]=EKF_SLAM(x,sigma,ut,y,dt);
    x_prev_stack=[x_prev_stack x];
    u_stack=[u_stack ut];
    y_stack=[y_stack y];
end

 ///////////
// Plots //
//////////

figure
plot(x_stack(1,:),x_stack(2,:),'b');
plot(x_prev_stack(1,:),x_prev_stack(2,:),'b--');
legend(["True trajectory";"Estimated trajectory"]);

figure
plot(x_stack(4),x_stack(5),'xb');
plot(x_prev_stack(4,size(x_prev_stack,2)),x_prev_stack(5,size(x_prev_stack,2)),'bd');

plot(x_stack(6),x_stack(7),'xr');
plot(x_prev_stack(6,size(x_prev_stack,2)),x_prev_stack(7,size(x_prev_stack,2)),'rd');
legend(["True landmark 1 localization";"Estimated landmark 1 localization";"True landmark 2 localization";"Estimated landmark 2 localization"])