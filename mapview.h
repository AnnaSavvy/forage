#pragma once

class WaveMap;

class MapView
{
    int cameraX = 0;
    int cameraY = 0;

    const WaveMap * _map = nullptr;

public:
    void setMap( const WaveMap * map );
    void moveCamera( int x, int y );
    void render() const;
};