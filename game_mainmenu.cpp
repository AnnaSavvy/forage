#include "gamemode.h"
#include "input.h"
#include "renderer.h"

ModeMainMenu::ModeMainMenu()
    : _map( 40 )
{
    _but.setWidth( 300 );
    _but.setHeight( 100 );
    _but.setX( 400 );
    _but.setY( 300 );
    _but.setLabel( "New Game" );
    _map.updateMap();
    _mapView.setMap( _map );
}

GameModeName ModeMainMenu::handleEvents()
{
    InputHandler input = InputHandler::Get();

    if ( input.handleEvent() ) {
        if ( input.isSet( InputHandler::MOUSE_CLICKED ) ) {
            if ( _but.getRect().contains( input.getClickPosition() ) ) {
                _but.setX( _but.getX() + 10 );
            }
        }
        return GameModeName::MAIN_MENU;
    }
    return GameModeName::QUIT_GAME;
}

void ModeMainMenu::update( float deltaTime )
{
    _mapView.moveCamera( 1, 1 );
}

void ModeMainMenu::render()
{
    _mapView.render();
    _but.render();
}

GameModeName runMainMenu()
{
    InputHandler input = InputHandler::Get();
    WaveMap map( 40 );
    MapView mapView;
    map.updateMap();
    mapView.setMap( map );

    while ( input.handleEvent() ) {
        mapView.moveCamera( 1, 1 );
        mapView.render();
    }
    return GameModeName::QUIT_GAME;
}
