#include "mapview.h"
#include "renderer.h"
#include "types.h"
#include "wave_function.h"

#define TILESIZE 64

MapView::MapView( bool infiniteScrolling )
    : infiniteScrolling( infiniteScrolling )
{}

void MapView::setMap( const MapBase & map )
{
    _map = &map;
    cameraX = 0;
    cameraY = 0;
}

void MapView::moveCamera( int x, int y )
{
    cameraX += x;
    cameraY += y;
}

void MapView::render() const
{
    if ( !_map )
        return;

    Rect target = { 0, 0, TILESIZE, TILESIZE };

    const size_t mapHeight = _map->getHeight();
    const size_t mapWidth = _map->getWidth();

    const Point & screenSize = RenderEngine::GetScreenSize();

    const int xStart = std::max( 0, cameraX / TILESIZE - 1 );
    const int yStart = std::max( 0, cameraY / TILESIZE - 1 );
    int xEnd = xStart + screenSize._x / TILESIZE + 2;
    int yEnd = yStart + screenSize._y / TILESIZE + 2;

    if ( !infiniteScrolling ) {
        if ( xEnd > mapWidth )
            xEnd = mapWidth;

        if ( yEnd > mapHeight )
            yEnd = mapHeight;
    }

    for ( int y = yStart; y < yEnd; y++ ) {
        for ( int x = xStart; x < xEnd; x++ ) {
            const int offset = ( x % 2 ) ? TILESIZE / 2 : 0;

            target._pos._x = x * TILESIZE - cameraX;
            target._pos._y = y * TILESIZE + offset - cameraY;

            const int xCoord = infiniteScrolling ? x % mapWidth : x;
            const int yCoord = infiniteScrolling ? y % mapWidth : y;

            const MapTile & ref = _map->getTile( yCoord * _map->getWidth() + xCoord );
            const WaveTile & tile = dynamic_cast<const WaveTile &>( ref );
            std::string texture = "assets/water.png";
            switch ( tile.type ) {
            case WaveTile::FOREST:
                texture = "assets/mountain.png";
                break;
            case WaveTile::TREES:
                texture = "assets/forest.png";
                break;
            case WaveTile::GRASS:
                texture = "assets/plains.png";
                break;
            case WaveTile::SAND:
                texture = "assets/swamp.png";
                break;
            case WaveTile::LAKE:
                texture = "assets/water.png";
                break;
            default:
                texture = "assets/water.png";
                break;
            }
            RenderEngine::Draw( texture, target );
        }
    }
}
