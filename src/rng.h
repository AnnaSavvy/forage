#pragma once
#include <random>

class RandomGenerator
{
    std::mt19937 engine;

public:
    RandomGenerator();
    RandomGenerator( int seed );

    bool roll( double chance );
    uint32_t next( int minimum, int maximum );

    static RandomGenerator & Get();
};
