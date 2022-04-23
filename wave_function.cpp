#include "wave_function.h"
#include <iostream>
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

std::vector<int> WaveTile::getPossibilities() const
{
    std::vector<int> retval;

    int typeCheck = 0x1;
    while ( typeCheck < TileTypes::ALL ) {
        if ( typeCheck & possible ) {
            retval.push_back( typeCheck );
        }
        typeCheck <<= 1;
    }
    return retval;
}

void WaveTile::limit( int fromTileType )
{
    // Rules!
    possible = LAKE1 | LAKE2 | DEEP_WATER;
}

WaveMap::WaveMap( size_t side )
{
    _map.reserve( side * side );
    _rowSize = side;
    for ( size_t i = 0; i < side * side; i++ ) {
        _map.emplace_back();
    }
}

size_t WaveMap::getSize() const
{
    return _map.size();
}

const WaveTile & WaveMap::getTile( size_t index ) const
{
    return _map[index];
}

std::vector<size_t> WaveMap::getAdjacent4( size_t index ) const
{
    std::vector<size_t> retval;
    retval.reserve( 4 );

    // TOP
    if ( index >= _rowSize ) {
        retval.push_back( index - _rowSize );
    }

    // BOTTOM
    if ( index + _rowSize < _map.size() ) {
        retval.push_back( index + _rowSize );
    }

    // LEFT
    const size_t positionX = index % _rowSize;
    if ( positionX > 0 ) {
        retval.push_back( index - 1 );
    }

    // RIGHT
    if ( positionX < _rowSize - 1 ) {
        retval.push_back( index + 1 );
    }

    return retval;
}

std::vector<size_t> WaveMap::getAdjacent8( size_t index ) const
{
    return std::vector<size_t>();
}

bool WaveMap::place( size_t index )
{
    if ( index < _map.size() ) {
        WaveTile & tile = _map[index];
        const int possible = tile.countPossibilities();
        if ( possible ) {
            int chosenOne = possible - 1;
            if ( possible > 1 ) {
                std::uniform_int_distribution<std::mt19937::result_type> distribution( 1, possible );

                chosenOne = distribution( rng );
            }
            tile.type = tile.getPossibilities()[chosenOne];

            for ( size_t adjacent : getAdjacent4( index ) ) {
                _map[adjacent].limit( tile.type );
            }
            return true;
        }
    }
    return false;
}

void WaveRenderer::renderMap( const WaveMap & map ) const
{
    std::cout << "======== MAP =========" << std::endl;
    for ( size_t i = 0; i < map.getSize(); i++ ) {
        renderTile( map.getTile( i ) );
        // TODO: fix columns
    }
    std::cout << "======================" << std::endl;
}

void WaveRenderer::renderTile( const WaveTile & tile ) const
{
    std::cout << " " << tile.type << std::endl;
}
