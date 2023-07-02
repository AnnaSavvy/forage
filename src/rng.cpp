#include "rng.h"

RandomGenerator::RandomGenerator() : engine(std::random_device{}()) {}

RandomGenerator::RandomGenerator( int seed ) : engine(seed) {}

bool RandomGenerator::roll( double chance )
{
    if (chance > 100)
        return true;

    std::uniform_real_distribution<double> distribution( 0.0, 1.0 );
    return distribution( engine ) < chance;
}

uint32_t RandomGenerator::next( int minimum, int maximum )
{
    std::uniform_int_distribution<uint32_t> distribution( minimum, maximum );
    return distribution( engine );
}

RandomGenerator & RandomGenerator::Get()
{
    static RandomGenerator generator;
    return generator;
}
