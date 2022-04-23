#pragma once
#include <bitset>
#include <vector>

enum TileTypes
{
    NONE = 0,
    FOREST = 0x1,
    TREES = 0x2,
    GRASS = 0x4,
    RIVER = 0x8,
    LAKE1 = 0x10,
    LAKE2 = 0x20,
    DEEP_WATER = 0x40,
    // FOREST = 0x80,
    // FOREST = 0x100,
    // FOREST = 0x200,
    // FOREST = 0x400,
    // FOREST = 0x800,
    ALL = 0x7F
};

struct WaveTile
{
    int type = NONE;
    int possible = ALL;

    int countPossibilities() const;
    std::vector<int> getPossibilities() const;
    void limit( int fromTileType, bool isDiagonal = false );
};

class WaveMap
{
    std::vector<WaveTile> _map;
    size_t _rowSize = 1;

public:
    WaveMap( size_t side );

    size_t getRowSize() const;
    const WaveTile & getTile( size_t index ) const;
    std::vector<size_t> getAdjacent4( size_t index ) const;
    std::vector<std::pair<size_t, bool> > getAdjacent8( size_t index ) const;
    bool place( size_t index, int type = NONE );

    bool waveIterate();
    bool waveSmallest();
    size_t findLeastPossibilities() const;
};

class WaveRenderer
{
public:
    virtual void renderMap( const WaveMap & map ) const;
    virtual void renderTile( const WaveTile & tile ) const;
};