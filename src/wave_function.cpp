#include "wave_function.h"
#include <iostream>

#include "rng.h"

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
        mask = FOREST | TREES | LAKE;
        break;
    case TREES:
        mask = FOREST | TREES | GRASS;
        break;
    case GRASS:
        mask = TREES | GRASS | SAND;
        break;
    case SAND:
        mask = GRASS | LAKE;
        break;
    case LAKE:
        mask = GRASS | SAND | LAKE;
        break;
    default:
        break;
    }
    possible = possible & mask;
}

WaveMap::WaveMap( size_t side )
    : MapBase(side, side)
{
    _map.reserve(side*side);
    for ( size_t i = 0; i < side * side; i++ ) {
        _map.emplace_back();
    }
    _map.begin()->possible = WaveTile::LAKE;
    place( 0 );
}

const MapTile & WaveMap::getTile( size_t index ) const
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

std::vector<size_t> WaveMap::getAdjacent6( size_t index ) const
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
        if ( index + _width < _map.size() ) {
            retval.push_back( index + _width - 1 );
        }
    }

    // RIGHT
    if ( xPosition < _width - 1 ) {
        retval.push_back( index + 1 );
        if ( index + _width < _map.size() ) {
            retval.push_back( index + _width + 1 );
        }
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
        const uint32_t id = RandomGenerator::Get().next( 0, possible.size() - 1 );
        tile.type = possible[id];
    }

    for ( size_t adjacent : getAdjacent6( index ) ) {
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

void WaveRenderer::renderTile( const WaveTile & tile ) const 
{
    switch ( tile.type ) {
    case WaveTile::FOREST:
        std::cout << "F";
        break;
    case WaveTile::TREES:
        std::cout << "T";
        break;
    case WaveTile::GRASS:
        std::cout << "G";
        break;
    case WaveTile::SAND:
        std::cout << "S";
        break;
    case WaveTile::LAKE:
        std::cout << "L";
        break;
    default:
        std::cout << " ";
        break;
    }
}
