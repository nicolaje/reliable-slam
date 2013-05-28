funcprot(0);
clear;

// Personal laptop workstation (LINUX)
path_in='/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Simulations/Scenarios/2D-4Transponders/';
path_out='/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/EKFSlam/Videos/2D-4Transponders/';

// UFRGS Laptop workstation
// path_in='/home/jeremy/workspace/reliable-slam/workspace/Simulations/Scenarios/2D-2Transponders/'

// Personal laptop workstation (WINDOWS)
// path_in='F:\Etudes\ENSTA-Bretagne\Stages\ENSI3-UFRGS\reliable-slam\workspace\Simulations\Scenarios\2D-2Transponders/';
raw_file=read_csv(path_in+'2D-4Transponders-Circle.res',';');

// avoid the first comment line + parse strings to double
data=evstr(raw_file(2:size(raw_file,1),:));

// Number of particles
K_param=500; 

// Number of landmarks
N_param=4;

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
// [[w(1:t)] [x_1:t] [y_1:t] [theta_1:t] [mux_l1_1:t] [muy_l1_1:t]  ... [mux_lN_1:t] [muy_lN_1:t] [sigmaxx_l1_1:t] [sigmaxy_l1_1:t] [sigmayx_l1_1:t] [sigmayy_l1_1:t] ... [sigmaxx_lN_1:t] [sigmaxy_lN_1:t] [sigmayx_lN_1:t] [sigmayy_lN_1:t]]
// w=weight
// Particle array (memory)
// It has 3-dimension (time t of the particle, member index of the particle members, index of the particle {k})
P=[];

// Initialize a particle-set according to the given "a-priori" initial state-vector,
// uniformely distributed in boxes for the robot pose,
// normally distributed for the landmarks position
// init_vector is [w x y theta l1_x l1_y l2_x l2_y...sigma...]
// pose_uncertainty contains the half-width of the pose boxes
function [Y]=init_particle_set(K,N,init_vector,pose_uncertainty)
    Y=zeros(1,4+(2+4)*N,K);
    low=init_vector(2:4)-pose_uncertainty(1:3);
    high=init_vector(2:4)+pose_uncertainty(1:3);
    Y(1,1,1:K)=1/K; // initialize weights
    
    for i=1:K,
        for j=1:3, // pose & orientation uncertainty
            Y(1,j+1,i)=grand(1,1,'unf',low(j),high(j));
        end
        for j=1:N, // landmarks uncertainty
            Y(1,4+2*(j-1):4+2*(j-1)+1,i)=grand(1,'mn',get_landmark_estimate(init_vector,j),get_landmark_covariance(init_vector,j))';
        end
    end
endfunction

// Get the estimate position of the ith landmark
function [L_pose]=get_landmark_estimate(particle,i)
    L_pose=[particle(1,4+1+(i-1)*2);
    particle(1,4+1+(i-1)*2+1)];
endfunction

// Get the covariance matrix of the ith landmark
function [Sigma]=get_landmark_covariance(particle,i)
    Sigma=[particle(1,4+1+N*2+(i-1)*4:4+1+N*2+(i-1)*4+1);
    particle(1,4+1+N*2+(i-1)*4+2:4+1+N*2+(i-1)*4+3)];
endfunction

// Observation function
function [z_hat]=h(particle)
    z_hat=[];
    for i=1:2:N_param,
        z_hat=[z_hat;sqrt((particle(2)-particle(4+2*i))^2+(particle(3)-particle(4+2*i+1)))];
    end
    return z_hat;
endfunction

// Returns the jacobian of the observation function
function [C]=jacobian_observation(particle)
    C=[];
    for i=1:N_param,
        dx=particle(2)-particle(4+(i-1)*2);
        dy=particle(3)-particle(4+(i-1)*2+1);
        d=sqrt((dx)^2+(dy)^2);
        dx=dx/d;
        dy=dy/d;

        C=[C;
        dx dy zeros(1,1+(i-1)*2)] // TODO
    end
        C=[0 0 1 0 0 0 0 0 0 0 0;
    (mut(1)-mut(4))/y(2) (mut(2)-mut(5))/y(2) 0 (mut(4)-mut(1))/y(2) (mut(5)-mut(2))/y(2) 0 0 0 0 0 0;
    (mut(1)-mut(6))/y(3) (mut(2)-mut(7))/y(3) 0 0 0 (mut(6)-mut(1))/y(3) (mut(7)-mut(2))/y(3) 0 0 0 0;
    (mut(1)-mut(8))/y(4) (mut(2)-mut(9))/y(4) 0 0 0 0 0 (mut(8)-mut(1))/y(4) (mut(9)-mut(2))/y(4) 0 0;
    (mut(1)-mut(10))/y(5) (mut(2)-mut(11))/y(5) 0 0 0 0 0 0 0 (mut(10)-mut(1))/y(5) (mut(11)-mut(2))/y(5)];
endfunction

// FastSLAM 1.0 algorithm with known correspondances landmarks
function [Y_pos]=fast_slam_1(z, u, Y_prev,dt,t)
    for l=1:N_param, // loop over all observed landmarks
        for k=1:K, // loop over all particles
            
            particle=Y_prev(size(Y_prev,1),:,k); // retrieve the k-th particle
            particle=sample_motion_model(particle,u,dt); // sample pose
            
            z_hat=h(particle);
            
            // Jacobian of the observation matrix (3 landmarks)
            C=[(mut(1)-mut(4))/y(2) (mut(2)-mut(5))/y(2) 0 (mut(4)-mut(1))/y(2) (mut(5)-mut(2))/y(2) 0 0;
            (mut(1)-mut(6))/y(3) (mut(2)-mut(7))/y(3) 0 0 0 (mut(6)-mut(1))/y(3) (mut(7)-mut(2))/y(3)];
            
            // Weight the particle
        end
        
        // Apply changes to Y_prev
        
        // Resample
    end
    
    // return the new particle set
endfunction

function [particle]=sample_motion_model(particle_prev,u,theta,dt)// TODO: particle as input/output
    u=u+grand(1,'mn',zeros(2,1),Mt); // Add noise to the control input
    particle_prev(2:4)=particle_prev(2:4)+[u(1)*dt*cos(x_prev(3));
    particle_prev(4)=theta;
    u(1)*dt*sin(x_prev(3));
    dt*u(2)+grand(1,1,'nor',0,sqrt(Ch))];
    particle=particle_prev;
endfunction

function [Y]=resampling_roulette()
    
endfunction

function [Y]=resampling_low_variance()
    
endfunction

function [pos,landmarks]=plot_set(Y)
    pos=[];
    landmarks=[];
    for i=1:size(Y,3),
        pos=[pos;Y(1,2,i) Y(1,3,i)]
        landmarks=[landmarks; Y(1,4:4+2*N_param+1,i)];
    end
    xpoly(pos(:,1),pos(:,2),"marks");
    handle=gce();
    handle.line_mode="off";
    handle.mark_size=0;
    handle.mark_mode="on";
    handle.mark_style=0;
    handle.mark_foreground=color('red');
    
    xpoly(landmarks(:,1),landmarks(:,2));
    handle_l=gce();
    handle_l.line_mode="off",
    handle_l.mark_size=0;
    handle_l.mark_mode="on";
    handle_l.mark_style=14;
    handle_l.mark_background=color('blue');
    
    xpoly(landmarks(:,3),landmarks(:,4));
    handle_l2=gce();
    handle_l2.line_mode="off",
    handle_l2.mark_size=0;
    handle_l2.mark_mode="on";
    handle_l2.mark_style=14;
    handle_l2.mark_background=color('orange');
    
    xpoly(landmarks(:,5),landmarks(:,6));
    handle_l3=gce();
    handle_l3.line_mode="off",
    handle_l3.mark_size=0;
    handle_l3.mark_mode="on";
    handle_l3.mark_style=14;
    handle_l3.mark_background=color('green');
    
    xpoly(landmarks(:,7),landmarks(:,8));
    handle_l4=gce();
    handle_l4.line_mode="off",
    handle_l4.mark_size=0;
    handle_l4.mark_mode="on";
    handle_l4.mark_style=14;
    handle_l4.mark_background=color('purple');
endfunction

[p_set]=init_particle_set(K_param,N_param,[0 0 0 0 20 0 -20 0 0 20 0 -20 16 0 0 16 16 0 0 16 16 0 0 16 16 0 0 16],[2 2 2]);
figure(1);
drawlater();
h_axes = gca();
h_axes.data_bounds = [-25,-45;25,35];
[pos,landmarks]=plot_set(p_set);
drawnow();