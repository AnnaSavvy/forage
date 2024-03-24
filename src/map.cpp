#include "map.h"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>


bool MapBase::isValid( size_t index ) const
{
    return index >= 0 && index < _width * _height;
}

size_t MapBase::getWidth() const
{
    return _width;
}

size_t MapBase::getHeight() const
{
    return _height;
}



HexMapManager::HexMapManager( int size )
    : MapBase( size, size )
{
    _tiles.resize( _width );
    for ( int i = 0; i < _width; i++ ) {
        _tiles[i].resize( _height );
    }
}

HexMapManager::~HexMapManager() {}

void HexMapManager::generateMap()
{
    // TODO: generate hexagonal map layout
}

bool HexMapManager::isOnMap( int x, int y )
{
    return ( x >= 0 && x < _width && y >= 0 && y < _height && y <= x + _width - 1 && y >= x - _height + 1 );
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
    // map[x][y] = occupied;
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
    if ( x < 0 || x >= _width || y < 0 || y >= _height ) {
        return nullptr;
    }

    // Use a 2D array to store the hex tiles for easy lookup
    return _tiles[x][y];
}

int HexMapManager::getDistance( MapTile * left, MapTile * right )
{
    if ( left && right ) {
        const int32_t du = right->y - left->y;
        const int32_t dv = ( right->x + right->y / 2 ) - ( left->x + left->y / 2 );

        if ( ( du >= 0 && dv >= 0 ) || ( du < 0 && dv < 0 ) ) {
            return std::max( std::abs( du ), std::abs( dv ) );
        }
        else {
            return std::abs( du ) + std::abs( dv );
        }
    }
    return 0;
}

int HexMapManager::getDistance( int index1, int index2 )
{
    if ( isValid( index1 ) && isValid( index2 ) ) {
        const int32_t x1 = index1 % _width;
        const int32_t y1 = index1 / _width;

        const int32_t x2 = index2 % _width;
        const int32_t y2 = index2 / _width;

        const int32_t du = y2 - y1;
        const int32_t dv = ( x2 + y2 / 2 ) - ( x1 + y1 / 2 );

        if ( ( du >= 0 && dv >= 0 ) || ( du < 0 && dv < 0 ) ) {
            return std::max( std::abs( du ), std::abs( dv ) );
        }
        else {
            return std::abs( du ) + std::abs( dv );
        }
    }
    return 0;
}

std::vector<MapTile *> HexMapManager::findPath( MapTile * startTile, MapTile * endTile )
{
    // Create open and closed sets
    std::vector<MapTile *> openSet;
    std::unordered_set<MapTile *> closedSet;

    // Add the starting tile to the open set
    openSet.push_back( startTile );

    // Create a map to keep track of each tile's parent tile
    std::unordered_map<MapTile *, MapTile *> parentMap;

    // Create a map to keep track of the cost to reach each tile
    std::unordered_map<MapTile *, int> gScore;
    gScore[startTile] = 0;

    // Create a map to keep track of the estimated total cost to reach the goal through each tile
    std::unordered_map<MapTile *, int> fScore;
    fScore[startTile] = getDistance( startTile, endTile );

    while ( !openSet.empty() ) {
        // Get the tile in the open set with the lowest fScore value
        auto currentTile = *std::min_element( openSet.begin(), openSet.end(), [&]( auto a, auto b ) { return fScore[a] < fScore[b]; } );

        // If the current tile is the end tile, reconstruct the path and return it
        if ( currentTile == endTile ) {
            std::vector<MapTile *> path;
            while ( currentTile != startTile ) {
                path.push_back( currentTile );
                currentTile = parentMap[currentTile];
            }
            path.push_back( startTile );
            std::reverse( path.begin(), path.end() );
            return path;
        }

        // Remove the current tile from the open set
        openSet.erase( std::remove( openSet.begin(), openSet.end(), currentTile ), openSet.end() );

        // Add the current tile to the closed set
        closedSet.insert( currentTile );

        // Loop through the current tile's neighbors
        for ( auto neighbor : getNeighbors( currentTile ) ) {
            // If the neighbor is already in the closed set, skip it
            if ( closedSet.count( neighbor ) > 0 ) {
                continue;
            }

            // Calculate the tentative gScore for the neighbor
            int tentativeGScore = gScore[currentTile] + getDistance( currentTile, neighbor );

            // If the neighbor is not in the open set, add it
            if ( std::find( openSet.begin(), openSet.end(), neighbor ) == openSet.end() ) {
                openSet.push_back( neighbor );
            }
            else if ( tentativeGScore >= gScore[neighbor] ) {
                // If the tentative gScore is greater than or equal to the current gScore for the neighbor, skip it
                continue;
            }

            // Update the parent and gScore maps for the neighbor
            parentMap[neighbor] = currentTile;
            gScore[neighbor] = tentativeGScore;

            // Update the fScore map for the neighbor
            fScore[neighbor] = gScore[neighbor] + getDistance( neighbor, endTile );
        }
    }

    // If we get here, there is no path to the end tile
    return std::vector<MapTile *>();
}
