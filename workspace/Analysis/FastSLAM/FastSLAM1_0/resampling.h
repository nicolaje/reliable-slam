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
    ReSampling();
    void resamplingRoulette(std::vector<Particle> particles);
};

#endif // RESAMPLING_H
