#pragma once
#include "map.h"
#include <string>

class MapView
{
    int cameraX = 0;
    int cameraY = 0;
    bool infiniteScrolling = false;
    std::string playerSprite = "";

    const MapBase * _map = nullptr;

public:
    MapView() = default;
    MapView( bool infiniteScrolling );
    void setPlayer( std::string sprite );
    void setMap( const MapBase & map );
    const MapTile * getPlayerTile() const;
    void moveCamera( int x, int y );
    bool movePlayer( int x, int y );
    void render() const;
};
