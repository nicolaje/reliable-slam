// Number of particles
K=1000; 

// Number of landmarks
N=3;

// 1 particle is 
// [w x_1:t y_1:t theta_1:t mux_l1 muy_l1 sigmaxx_l1 sigmaxy_l1 sigmayx_l1 sigmayy_l1 ... mux_lN muy_lN sigmaxx_lN sigmaxy_lN sigmayx_lN sigmayy_lN]
// w=weight
// of size (1, 1+3*t+6N)
// Particle array (memory)
P=[];

// FastSLAM 1.0 algorithm with known correspondances landmarks
function [Y_pos]=fast_slam_1(z, u, Y_prev)
    for k=1:K,
        
    end
endfunction

function [Y]=resampling_roulette()
    
endfunction

function [Y]=resampling_low_variance()
    
endfunction