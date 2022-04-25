#include "wave_function.h"
#include <random>
#include <iostream>

namespace
{
    std::random_device dev;
    std::mt19937 rng( dev() );
}

std::vector<int> WaveTile::getPossibilities() const
{
    std::vector<int> retval;
    int check = 1;
    while ( check < ALL ) {
        if ( check & possible ) {
            retval.push_back( check );
        }
        check <<= 1;
    }
    return retval;
}

void WaveTile::limit( int fromTileType ) 
{
    int mask = 0;
    switch ( fromTileType ) {
    case FOREST:
        mask = FOREST | TREES;
        break;
    case TREES:
        mask = FOREST | TREES | GRASS;
        break;
    case GRASS:
        mask = TREES | GRASS | SAND;
        break;
    case SAND:
        mask = GRASS | SAND | LAKE;
        break;
    case LAKE:
        mask = SAND | LAKE;
        break;
    default:
        break;
    }
    possible = possible & mask;
}

WaveMap::WaveMap( size_t side )
{
    _map.reserve(side*side);
    _width = side;
    for ( size_t i = 0; i < side * side; i++ ) {
        _map.emplace_back();
    }
}

size_t WaveMap::getWidth() const
{
    return _width;
}

const WaveTile & WaveMap::getTile( size_t index ) const
{
    return _map[index];
}

std::vector<size_t> WaveMap::getAdjacent4( size_t index ) const
{
    std::vector<size_t> retval;

    // TOP
    if ( index >= _width ) {
        retval.push_back( index - _width );
    }

    const size_t xPosition = index % _width;
    // LEFT
    if ( xPosition > 0 ) {
        retval.push_back( index - 1 );
    }

    // RIGHT
    if ( xPosition < _width - 1 ) {
        retval.push_back( index + 1 );
    }

    // BOTTOM
    if ( index + _width < _map.size() ) {
        retval.push_back( index + _width );
    }

    return retval;
}

std::vector<size_t> WaveMap::getAdjacent8( size_t index ) const
{
    return std::vector<size_t>();
}

bool WaveMap::place( size_t index )
{
    WaveTile & tile = _map[index];
    std::vector<int> possible = tile.getPossibilities();
    if ( possible.size() == 0 )
        return false;

    if ( possible.size() == 1 ) {
        tile.type = possible[0];
    }
    else {
        std::uniform_int_distribution<std::mt19937::result_type> distribution( 1, possible.size() );
        tile.type = possible[distribution( dev ) - 1];
    }

    for ( size_t adjacent : getAdjacent4( index ) ) {
        _map[adjacent].limit( tile.type );
    }
    return true;
}

bool WaveMap::updateMap()
{
    for ( size_t i = 0; i < _map.size(); i++ ) {
        place( i );
    }
    return true;
}

void WaveRenderer::renderMap( const WaveMap & map ) const
{
    std::cout << "=== OUR MAP: ===" << std::endl;
    size_t mapSize = map.getWidth();
    for ( size_t x = 0; x < mapSize; x++ ) {
        for ( size_t y = 0; y < mapSize; y++ ) {
            renderTile( map.getTile( x * mapSize + y ) );
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "=== END MAP: ===" << std::endl;
}

void WaveRenderer::renderTile( const WaveTile & tile ) const 
{
    switch ( tile.type ) {
    case FOREST:
        std::cout << "F";
        break;
    case TREES:
        std::cout << "T";
        break;
    case GRASS:
        std::cout << "G";
        break;
    case SAND:
        std::cout << "S";
        break;
    case LAKE:
        std::cout << "L";
        break;
    default:
        std::cout << " ";
        break;
    }
}
