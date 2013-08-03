#include "resampling.h"
#include <iostream>
#include "fastslam.h"
#include "../../General/Utils/utils.h"

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
    ibex::IntervalVector pos(3);
    ibex::IntervalVector orr(3);
    std::vector<ibex::IntervalVector> map;
    for(int i=0;i<3;i++){
        pos[i]=box[i];
        orr[i]=box[3+i];
    }

    for(int i=0;i<particles[0].getMap().size();i++){
        ibex::IntervalVector v(3);
        for(int j=0;j<3;j++)
            v[j]=box[6+i*3+j];
        map.push_back(v);
    }

    int nbPos=0;
    int nbOr=0;
    std::vector<Particle> kept;
    for(int i=0;i<particles.size();i++){
        if(!Utils::eigenVectorToIntervalVector(particles[i].toVector()).is_subset(box))
            particles[i].shakeMap(map);
        kept.push_back(particles[i]);
        nbPos+=Utils::eigenVectorToIntervalVector(particles[i].getPosition()).is_subset(pos)?1:0;
        nbOr+=Utils::eigenVectorToIntervalVector(particles[i].getOrientation()).is_subset(orr)?1:0;
    }
    std::cout << "Nb of consistent position: " << nbPos << std::endl;
    std::cout << "Nb of consistent orientation: " << nbOr << std::endl;
    std::cout << "Kept: " << kept.size() << std::endl;
    kept=normalize(kept);
    return kept;
}

std::vector<Particle> ReSampling::normalize(std::vector<Particle> particles)
{
    double sum=0;
    for(int i=0;i<particles.size();i++)
        sum+=particles[i].getWeight();
    for(int i=0;i<particles.size();i++)
        particles[i].normalizeWeight(sum);
    return particles;
}
