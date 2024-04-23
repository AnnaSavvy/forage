#include "mapview.h"
#include "renderer.h"
#include "types.h"
#include "wave_function.h"

#define TILESIZE 64

MapView::MapView( bool infiniteScrolling )
    : infiniteScrolling( infiniteScrolling )
{}

void MapView::setPlayer( std::string sprite )
{
    playerSprite = sprite;
}

void MapView::setMap( const MapBase & map )
{
    _map = &map;
    cameraX = 0;
    cameraY = 0;
}

const MapTile * MapView::getPlayerTile() const
{
    if ( !_map ) {
        return nullptr;
    }

    size_t index = _map->getWidth() * cameraY / 64 + cameraX % 64;
    return _map->isValid( index ) ? &_map->getTile( index ) : nullptr;
}

void MapView::moveCamera( int x, int y )
{
    cameraX += x;
    cameraY += y;
}

bool MapView::movePlayer( int x, int y )
{
    const bool movedX = ( cameraX / TILESIZE ) != ( ( cameraX + x ) / TILESIZE );
    const bool movedY = ( cameraY / TILESIZE ) != ( ( cameraY + y ) / TILESIZE );
    cameraX += x;
    cameraY += y;
    return movedX || movedY;
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
    int xEnd = xStart + screenSize.x / TILESIZE + 2;
    int yEnd = yStart + screenSize.y / TILESIZE + 3;

    if ( !infiniteScrolling ) {
        if ( xEnd > mapWidth )
            xEnd = mapWidth;

        if ( yEnd > mapHeight )
            yEnd = mapHeight;
    }

    for ( int y = yStart; y < yEnd; y++ ) {
        for ( int x = xStart; x < xEnd; x++ ) {
            const int offset = ( x % 2 ) ? TILESIZE / 2 : 0;

            target.pos.x = x * TILESIZE - cameraX;
            target.pos.y = y * TILESIZE + offset - cameraY;

            const int xCoord = infiniteScrolling ? x % mapWidth : x;
            const int yCoord = infiniteScrolling ? y % mapWidth : y;

            const MapTile & ref = _map->getTile( yCoord * _map->getWidth() + xCoord );
            const WaveTile & tile = dynamic_cast<const WaveTile &>( ref );
            std::string texture = "assets/t_water.png";
            switch ( tile.type ) {
            case WaveTile::MOUNTAIN:
                texture = "assets/t_mountain_snow.png";
                break;
            case WaveTile::HILL:
                texture = "assets/t_mountain.png";
                break;
            case WaveTile::DEEP_FOREST:
                texture = "assets/t_forest_deep.png";
                break;
            case WaveTile::FOREST:
                texture = "assets/t_forest.png";
                break;
            case WaveTile::GRASS:
                texture = "assets/t_plains.png";
                break;
            case WaveTile::SAND:
                texture = "assets/t_swamp.png";
                break;
            case WaveTile::WATER:
                texture = "assets/t_water.png";
                break;
            case WaveTile::DEEP_WATER:
                texture = "assets/t_water_deep.png";
                break;
            default:
                texture = "assets/t_water.png";
                break;
            }
            RenderEngine::Draw( texture, target );
        }
    }

    if ( !playerSprite.empty() ) {
        Rect center;
        center.pos = { screenSize.x / 2, screenSize.y / 2 };
        center.size = { TILESIZE, TILESIZE };
        RenderEngine::Draw( playerSprite, center );
    }
}
