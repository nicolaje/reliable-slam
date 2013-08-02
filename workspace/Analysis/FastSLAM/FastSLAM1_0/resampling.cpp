#include "resampling.h"
#include <iostream>
#include "fastslam.h"

std::vector<Particle> ReSampling::resamplingRoulette(std::vector<Particle> particles)
{
    std::vector<Particle> res;
    std::vector<double> weights;
    std::uniform_real_distribution<double> d(0.0,1.0);
    for(uint i=0;i<particles.size();i++){
        weights.push_back(d(FastSLAM::generator));
    }
    for(uint i=0;i<particles.size();i++){
        double wsum=particles[0].getWeight(),wobj=weights[i];
        int idx=1;
        while(wsum<wobj){
            wsum+=particles[idx].getWeight();
            idx++;
        }
        res.push_back(particles[idx-1]);
    }
    return res;
}

std::vector<Particle>  ReSampling::resamplingPercentil(std::vector<Particle> particles, int percentil)
{
    std::vector<Particle> res;

    return res;
}

std::vector<Particle> ReSampling::resamplingHybrid(std::vector<Particle> particles, ibex::IntervalVector box)
{
    // First, remove non-consistent particles
    for(int i=0;i<particles.size();i++)
    {

    }
}
