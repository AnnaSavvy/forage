#pragma once

class MapBase;

class MapView
{
    int cameraX = 0;
    int cameraY = 0;
    bool infiniteScrolling = false;

    const MapBase * _map = nullptr;

public:
    MapView() = default;
    MapView( bool infiniteScrolling );
    void setMap( const MapBase & map );
    void moveCamera( int x, int y );
    void render() const;
};
