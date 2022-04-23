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
    while ( typeCheck <= TileTypes::ALL ) {
        if ( typeCheck & possible ) {
            retval.push_back( typeCheck );
        }
        typeCheck <<= 1;
    }
    return retval;
}

void WaveTile::limit( int fromTileType, bool isDiagonal )
{
    int mask = 0;
    // Rules!
    switch ( fromTileType ) {
    case FOREST:
        mask = FOREST | TREES;
        break;
    case TREES:
        mask = FOREST | TREES | GRASS;
        break;
    case GRASS:
        mask = TREES | GRASS | RIVER;
        break;
    case RIVER:
        mask = GRASS | RIVER | LAKE1;
        break;
    case LAKE1:
        mask = RIVER | LAKE1 | LAKE2;
        break;
    case LAKE2:
        mask = LAKE1 | LAKE2 | DEEP_WATER;
        break;
    case DEEP_WATER:
        mask = LAKE2 | DEEP_WATER;
        break;
    default:
        break;
    }
    // Disable non-masked bits
    possible = possible & mask;
}

WaveMap::WaveMap( size_t side )
{
    _map.reserve( side * side );
    _rowSize = side;
    for ( size_t i = 0; i < side * side; i++ ) {
        _map.emplace_back();
    }
}

size_t WaveMap::getRowSize() const
{
    return _rowSize;
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

std::vector<std::pair<size_t, bool> > WaveMap::getAdjacent8( size_t index ) const
{
    std::vector<std::pair<size_t, bool> > retval;
    retval.reserve( 8 );

    const size_t positionX = index % _rowSize;
    const size_t xLimit = _rowSize - 1;

    // TOP
    if ( index > _rowSize && positionX > 0 ) {
        retval.emplace_back( index - _rowSize - 1, true );
    }
    if ( index >= _rowSize ) {
        retval.emplace_back( index - _rowSize, false );
        if ( positionX < xLimit ) {
            retval.emplace_back( index - _rowSize + 1, true );
        }
    }

    // LEFT
    if ( positionX > 0 ) {
        retval.emplace_back( index - 1, false );
    }
    // RIGHT
    if ( positionX < xLimit ) {
        retval.emplace_back( index + 1, false );
    }

    // BOTTOM
    if ( index + _rowSize < _map.size() ) {
        if ( positionX > 0 ) {
            retval.emplace_back( index + _rowSize - 1, true );
        }

        retval.emplace_back( index + _rowSize, false );
    }
    if ( index + _rowSize + 1 < _map.size() ) {
        retval.emplace_back( index + _rowSize + 1, true );
    }

    return retval;
}

bool WaveMap::place( size_t index, int type )
{
    if ( index < _map.size() ) {
        WaveTile & tile = _map[index];

        if ( type == NONE ) {
            const int possible = tile.countPossibilities();
            if ( possible ) {
                int chosenOne = possible;
                if ( possible > 1 ) {
                    std::uniform_int_distribution<std::mt19937::result_type> distribution( 1, possible );

                    chosenOne = distribution( rng );
                }
                type = tile.getPossibilities()[chosenOne - 1];

                // for ( std::pair<size_t, bool> adjacent : getAdjacent8( index ) ) {
                //    _map[adjacent.first].limit( tile.type, adjacent.second );
                //}
            }
        }
        tile.type = type;

        for ( size_t adjacent : getAdjacent4( index ) ) {
            _map[adjacent].limit( tile.type );
        }

        return true;
    }
    return false;
}

bool WaveMap::waveIterate()
{
    for ( size_t index = 0; index < _map.size(); index++ ) {
        if ( !place( index ) ) {
            // something went wrong!
            return false;
        }
    }
    return true;
}

bool WaveMap::waveSmallest()
{
    size_t lastIndex = findLeastPossibilities();
    place( lastIndex, GRASS );

    size_t nextIndex = findLeastPossibilities();
    while ( nextIndex != lastIndex ) {
        place( nextIndex );
        lastIndex = nextIndex;
        nextIndex = findLeastPossibilities();
    }
    return true;
}

size_t WaveMap::findLeastPossibilities() const
{
    size_t bestIndex = _map.size() / 2;
    int leastPossibilities = ALL;

    for ( size_t index = 0; index < _map.size(); index++ ) {
        int count = _map[index].countPossibilities();
        if ( count < leastPossibilities && _map[index].type == NONE ) {
            bestIndex = index;
            leastPossibilities = count;
        }
    }

    return bestIndex;
}

void WaveRenderer::renderMap( const WaveMap & map ) const
{
    std::cout << "======== MAP =========" << std::endl;

    const size_t rowSize = map.getRowSize();
    for ( size_t x = 0; x < rowSize; x++ ) {
        for ( size_t y = 0; y < rowSize; y++ ) {
            renderTile( map.getTile( y * rowSize + x ) );
        }
        std::cout << std::endl;
    }
    std::cout << "======================" << std::endl;
}

void WaveRenderer::renderTile( const WaveTile & tile ) const
{
    switch ( tile.type ) {
    case FOREST:
        std::cout << " FD";
        break;
    case TREES:
        std::cout << " FS";
        break;
    case GRASS:
        std::cout << " GR";
        break;
    case RIVER:
        std::cout << " RI";
        break;
    case LAKE1:
        std::cout << " L1";
        break;
    case LAKE2:
        std::cout << " L2";
        break;
    case DEEP_WATER:
        std::cout << " DW";
        break;
    default:
        std::cout << "   ";
        break;
    }
}
