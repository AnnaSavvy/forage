#include "wave_function.h"
#include <random>

namespace
{
    std::random_device dev;
    std::mt19937 rng( dev() );
}

int WaveTile::countPossibilities() const
{
    int count = 0;
    int temp = possible;
    while ( temp ) {
        count += temp & 1;
        temp >>= 1;
    }
    return count;
}

void WaveTile::limit( int fromTileType )
{
    // Rules!
    possible = LAKE1 | LAKE2 | DEEP_WATER;
}

WaveMap::WaveMap( int side )
{
    _map.reserve( side * side );
    _rowSize = side;
    for ( int i = 0; i < side * side; i++ ) {
        _map.emplace_back();
    }
}

WaveTile & WaveMap::getTile( size_t index )
{
    return _map[index];
}

std::vector<size_t> WaveMap::getAdjacent4( size_t index ) const
{
    std::vector<size_t> retval;
    retval.reserve( 4 );

    return retval;
}

std::vector<size_t> WaveMap::getAdjacent8( size_t index ) const
{
    return std::vector<size_t>();
}

bool WaveMap::place( size_t index )
{
    if ( index < _map.size() ) {
        const int possible = _map[index].countPossibilities();
        if ( possible ) {
            std::uniform_int_distribution<std::mt19937::result_type> distribution( 1, _map[index].countPossibilities() );

            int result = distribution( rng );
        }
    }
    return false;
}

void WaveRenderer::renderMap( const WaveMap & map ) const {}

void WaveRenderer::renderTile( const WaveMap & tile ) const {}
