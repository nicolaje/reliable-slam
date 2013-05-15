// Number of particles
K=1000; 

// Number of landmarks
N=3;

// Degrees to radians
deg2rad=%pi/180;

// Variance of the heading sensor
Ch=(0.02*deg2rad)^2;

// Covariance of the motion noise
Mt=[0.04^2 0;
0 (0.01*deg2rad)^2];

// Variance of the range sensor
Cr=0.3^2;

// 1 particle is 
// [w x_1:t y_1:t theta_1:t mux_l1 muy_l1 sigmaxx_l1 sigmaxy_l1 sigmayx_l1 sigmayy_l1 ... mux_lN muy_lN sigmaxx_lN sigmaxy_lN sigmayx_lN sigmayy_lN]
// w=weight
// of size (1, 1+3*t+6N)
// Particle array (memory)
P=[];

function [Y]=init_particle_set(K,N)
    
endfunction

// FastSLAM 1.0 algorithm with known correspondances landmarks
function [Y_pos]=fast_slam_1(z, u, Y_prev,dt)
    for k=1:K,
        particle=Y_prev(k,:);
        particle(2:4)=sample_motion_model(particle(2:4),u,dt); // sample pose
        
    end
endfunction

function [x]=sample_motion_model(x_prev,u,dt)
    u=u+grand(1,'mn',zeros(2,1),Mt); // Add noise to the control input
    x=x_prev+[u(1)*dt*cos(x_prev(3));
    u(1)*dt*sin(x_prev(3));
    dt*u(2)+grand(1,1,'nor',0,Ch)];
endfunction

function [Y]=resampling_roulette()
    
endfunction

function [Y]=resampling_low_variance()
    
endfunction