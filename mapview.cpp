#include "mapview.h"
#include "asset_loader.h"
#include "renderer.h"
#include "wave_function.h"

#include <SDL.h>

#define TILESIZE 64

void MapView::setMap( const MapBase * map )
{
    _map = map;
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

    SDL_Rect target;
    target.x = 0;
    target.y = 0;
    target.h = TILESIZE;
    target.w = TILESIZE;

    for ( int y = 0; y < _map->getHeight(); y++ ) {
        for ( int x = 0; x < _map->getWidth(); x++ ) {
            const int offset = ( x % 2 ) ? TILESIZE / 2 : 0;

            target.x = x * TILESIZE + cameraX;
            target.y = y * TILESIZE + offset + cameraY;

            const MapTile & ref = _map->getTile( y * _map->getWidth() + x );
            const WaveTile & tile = dynamic_cast<const WaveTile &>( ref );
            std::string texture = "assets/water.png";
            switch ( tile.type ) {
            case FOREST:
                texture = "assets/mountain.png";
                break;
            case TREES:
                texture = "assets/forest.png";
                break;
            case GRASS:
                texture = "assets/plains.png";
                break;
            case SAND:
                texture = "assets/swamp.png";
                break;
            case LAKE:
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
