#pragma once
#include <random>

#include <cassert>

class RandomGenerator
{
    std::mt19937 engine;

public:
    RandomGenerator();
    RandomGenerator( int seed );

    bool roll( double chance );
    uint32_t next( int minimum, int maximum );

    template <typename T>
    inline T randomElement( const std::vector<T> & vector )
    {
        const size_t size = vector.size();
        assert( size );

        if ( size ) {
            return vector[next( 0, vector.size() - 1 )];
        }
        return T();
    }

    static RandomGenerator & Get();
};
