#pragma once
#include <bitset>
#include <vector>

#include "map.h"

struct WaveTile : public MapTile
{
    enum TileTypes
    {
        NONE = 0,
        MOUNTAIN = 0x1,
        HILL = 0x2,
        DEEP_FOREST = 0x4,
        FOREST = 0x8,
        GRASS = 0x10,
        SAND = 0x20,
        WATER = 0x40,
        DEEP_WATER = 0x80,
        ALL = 0xFF
    };

    int type = NONE;
    int possible = ALL;

    std::vector<int> getPossibilities() const;
    void limit( int fromTileType );
};

class WaveMap : public MapBase
{
    std::vector<WaveTile> _map;

public:
    WaveMap( size_t side );

    const MapTile & getTile( size_t index ) const;
    std::vector<size_t> getAdjacent4( size_t index ) const;
    std::vector<size_t> getAdjacent6( size_t index ) const;
    std::vector<size_t> getAdjacent8( size_t index ) const;
    bool place( size_t index );

    bool updateMap();

    // findSmallest
};

class WaveRenderer
{
public:
    virtual void renderTile( const WaveTile & tile ) const;
};