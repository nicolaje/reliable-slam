#ifndef RESAMPLING_H
#define RESAMPLING_H
#include <vector>
#include "particle.h"

/**
 * @brief The ReSampling class contains some methods to resample a particle population.
 */
class ReSampling
{
public:
    static std::vector<Particle> resamplingRoulette(std::vector<Particle> particles);
    static std::vector<Particle> resamplingPercentil(std::vector<Particle> particles, int percentil);
};

#endif // RESAMPLING_H
