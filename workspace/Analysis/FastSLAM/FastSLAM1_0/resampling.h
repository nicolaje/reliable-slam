#ifndef RESAMPLING_H
#include <vector>
#include "particle.h"
#include <ibex/ibex.h>
#define RESAMPLING_H

/**
 * @brief The ReSampling class contains some methods to resample a particle population.
 */
class ReSampling
{
public:
    static std::vector<Particle> resamplingRoulette(std::vector<Particle> particles);
    static std::vector<Particle> resamplingPercentil(std::vector<Particle> particles, int percentil);

    /**
     * @brief resamplingHybrid
     * @param particles
     * @param box
     * @return
     */
    static std::vector<Particle> resamplingHybrid(std::vector<Particle> particles, ibex::IntervalVector box);
};

#endif // RESAMPLING_H
