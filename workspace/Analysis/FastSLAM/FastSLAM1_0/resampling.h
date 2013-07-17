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
    static void resamplingRoulette(std::vector<Particle> particles);
    static void resamplingQuartil(std::vector<Particle> particles, int quartil);
};

#endif // RESAMPLING_H
