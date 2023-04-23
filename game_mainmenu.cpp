#include "game_mainmenu.h"
#include "input.h"
#include "renderer.h"

ModeMainMenu::ModeMainMenu()
    : _backgroundMap( 100 )
    , _but( 400, 300, 270, 80, "New Game" )
{
    _backgroundMap.updateMap();
    _mapView.setMap( _backgroundMap );

    Style buttonStyle;
    buttonStyle.font = StandardFont::REGULAR_BOLD;
    buttonStyle.textColor = StandardColor::HIGHLIGHT_RED;
    buttonStyle.borderColor = StandardColor::DARK_GREY;
    buttonStyle.borderWidth = 5;
    _but.setStyle( buttonStyle );
}

GameModeName ModeMainMenu::handleEvents()
{
    InputHandler input = InputHandler::Get();

    if ( input.handleEvent() ) {
        if ( input.isSet( InputHandler::MOUSE_CLICKED ) ) {
            if ( _but.getRect().contains( input.getClickPosition() ) ) {
                return GameModeName::NEW_GAME;
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
