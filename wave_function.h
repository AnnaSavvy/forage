#pragma once
#include <bitset>
#include <vector>

enum TileTypes
{
    NONE = 0,
    FOREST = 0x1,
    TREES = 0x2,
    GRASS = 0x4,
    SAND = 0x8,
    LAKE = 0x10,
    ALL = 0x1F
};

struct WaveTile
{
    int type = NONE;
    int possible = ALL;

    std::vector<int> getPossibilities() const;
    void limit( int fromTileType );
};

class WaveMap
{
    std::vector<WaveTile> _map;
    size_t _width = 1;

public:
    WaveMap( size_t side );

    size_t getWidth() const;
    const WaveTile & getTile( size_t index ) const;
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
    virtual void renderMap( const WaveMap & map ) const;
    virtual void renderTile( const WaveTile & tile ) const;
};