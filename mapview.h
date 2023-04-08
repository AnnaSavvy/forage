#pragma once

class MapBase;

class MapView
{
    int cameraX = 0;
    int cameraY = 0;

    const MapBase * _map = nullptr;

public:
    void setMap( const MapBase * map );
    void moveCamera( int x, int y );
    void render() const;
};
