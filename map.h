#pragma once
#include <vector>

struct MapTile
{
    int x;
    int y;
};

class HexMapManager
{
public:
    HexMapManager( int size );
    ~HexMapManager();

    void generateMap();
    bool isOnMap( int x, int y );
    bool isOccupied( int x, int y );
    bool isValid( int index );
    void setOccupied( int x, int y, bool occupied );
    MapTile * getTileAt( int x, int y );
    std::vector<MapTile *> findPath( MapTile * startTile, MapTile * endTile );
    std::vector<MapTile *> getNeighbors( MapTile * tile );
    int getDistance( int index1, int index2 );
    int getDistance( MapTile * left, MapTile * right );

private:
    size_t width;
    size_t height;
    std::vector<std::vector<MapTile *> > _tiles;
};

HexMapManager::HexMapManager( int size )
    : width( size )
    , height(size)
{
    _tiles.resize( width );
    for ( int i = 0; i < width; i++ ) {
        _tiles[i].resize( height );
    }
}

HexMapManager::~HexMapManager() {}

void HexMapManager::generateMap()
{
    // TODO: generate hexagonal map layout
}

bool HexMapManager::isOnMap( int x, int y )
{
    return ( x >= 0 && x < width && y >= 0 && y < height && y <= x + width - 1 && y >= x - height + 1 );
}

bool HexMapManager::isOccupied( int x, int y )
{
    if ( !isOnMap( x, y ) ) {
        return true;
    }
    return _tiles[x][y];
}

void HexMapManager::setOccupied( int x, int y, bool occupied )
{
    if ( !isOnMap( x, y ) ) {
        return; 
    }
    //map[x][y] = occupied;
}

std::vector<MapTile *> HexMapManager::getNeighbors( MapTile * tile )
{
    std::vector<MapTile *> neighbors;
    const int x = tile->x;
    const int y = tile->y;

    // Clockwise order starting from the right neighbor
    MapTile * rightNeighbor = getTileAt( x + 1, y );
    MapTile * topRightNeighbor = getTileAt( x, y - 1 );
    MapTile * topLeftNeighbor = getTileAt( x - 1, y - 1 );
    MapTile * leftNeighbor = getTileAt( x - 1, y );
    MapTile * bottomLeftNeighbor = getTileAt( x, y + 1 );
    MapTile * bottomRightNeighbor = getTileAt( x + 1, y + 1 );

    // Only add non-null neighbors
    if ( rightNeighbor != nullptr ) {
        neighbors.push_back( rightNeighbor );
    }
    if ( topRightNeighbor != nullptr ) {
        neighbors.push_back( topRightNeighbor );
    }
    if ( topLeftNeighbor != nullptr ) {
        neighbors.push_back( topLeftNeighbor );
    }
    if ( leftNeighbor != nullptr ) {
        neighbors.push_back( leftNeighbor );
    }
    if ( bottomLeftNeighbor != nullptr ) {
        neighbors.push_back( bottomLeftNeighbor );
    }
    if ( bottomRightNeighbor != nullptr ) {
        neighbors.push_back( bottomRightNeighbor );
    }

    return neighbors;
}

MapTile * HexMapManager::getTileAt( int x, int y )
{
    // Check if the tile is out of bounds
    if ( x < 0 || x >= width || y < 0 || y >= height ) {
        return nullptr;
    }

    // Use a 2D array to store the hex tiles for easy lookup
    return _tiles[x][y];
}
