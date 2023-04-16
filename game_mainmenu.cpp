#include "gamemode.h"
#include "input.h"
#include "renderer.h"
#include "ui.h"
#include "ui_style.h"

ModeMainMenu::ModeMainMenu()
    : _map( 40 )
{
    _map.updateMap();
    _mapView.setMap( _map );
}

GameModeName ModeMainMenu::handleEvents()
{
    InputHandler input = InputHandler::Get();

    if ( input.handleEvent() ) {
        return GameModeName::MAIN_MENU;
    }
    return GameModeName::QUIT_GAME;
}

void ModeMainMenu::update( float deltaTime ) {
    _mapView.moveCamera( 1, 1 );
}

void ModeMainMenu::render() {
    _mapView.render();

    RenderEngine::DrawRect( { 300, 300, 300, 90 }, {} );
    RenderEngine::DrawText( "Welcome!", { 340, 330, 400, 100 } );
}

GameModeName runMainMenu()
{
    InputHandler input = InputHandler::Get();
    WaveMap map(40);
    MapView mapView;
    map.updateMap();
    mapView.setMap( map );

    while ( input.handleEvent() ) {
        mapView.moveCamera( 1, 1 );
        mapView.render();

        RenderEngine::DrawRect( { 300, 300, 300, 90 }, {} );
        RenderEngine::DrawText( "Welcome!", { 340, 330, 400, 100 } );
    }
    return GameModeName::QUIT_GAME;
}
