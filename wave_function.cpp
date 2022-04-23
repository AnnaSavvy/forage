#include "wave_function.h"

int WaveTile::countPossibilities() const
{
    return 0;
}

void WaveTile::limit( int fromTileType ) {}

WaveMap::WaveMap( int side ) {}

WaveTile & WaveMap::getTile( size_t index )
{
    // TODO: insert return statement here
}

std::vector<size_t> WaveMap::getAdjacent4( size_t index ) const
{
    return std::vector<size_t>();
}

std::vector<size_t> WaveMap::getAdjacent8( size_t index ) const
{
    return std::vector<size_t>();
}

bool WaveMap::place( size_t index )
{
    return false;
}

void WaveRenderer::renderMap( const WaveMap & map ) const {}

void WaveRenderer::renderTile( const WaveMap & tile ) const {}
