#include "gamemode.h"
#include "input.h"
#include "renderer.h"

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
