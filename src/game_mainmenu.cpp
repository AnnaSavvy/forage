#include "game_mainmenu.h"
#include "input.h"
#include "renderer.h"

ModeMainMenu::ModeMainMenu()
    : _backgroundMap( 100 )
    , _mapView( true )
    , _title( { 200, 150 }, "Best Damn Game", StandardFont::MENU_HUGE_TITLE, StandardColor::WHITE )
    , _bNewGame( 400, 500, 270, 80, "New Game" )
    , _bLoadGame( 400, 600, 270, 80, "Load Game" )
    , _bOptions( 400, 700, 270, 80, "Options" )
    , _bQuitGame( 400, 800, 270, 80, "Quit Game" )
{
    name = GameModeName::MAIN_MENU;

    _backgroundMap.updateMap();
    _mapView.setMap( _backgroundMap );

    Style buttonStyle;
    buttonStyle.font = StandardFont::REGULAR_BOLD;
    buttonStyle.textColor = StandardColor::HIGHLIGHT_RED;
    buttonStyle.borderColor = StandardColor::DARK_GREY;
    buttonStyle.borderWidth = 5;
    _bNewGame.setStyle( buttonStyle );
    _bLoadGame.setStyle( buttonStyle );
    _bOptions.setStyle( buttonStyle );
    _bQuitGame.setStyle( buttonStyle );
}

GameModeName ModeMainMenu::handleEvents()
{
    InputHandler & input = InputHandler::Get();

    if ( input.handleEvent() ) {
        if ( input.isSet( InputHandler::MOUSE_CLICKED ) ) {
            const Point & mouseClick = input.getClickPosition();
            if ( _bNewGame.getRect().contains( mouseClick ) ) {
                return GameModeName::NEW_GAME;
            }
            else if ( _bLoadGame.getRect().contains( mouseClick ) ) {
                return GameModeName::LOAD_GAME;
            }
            else if ( _bOptions.getRect().contains( mouseClick ) ) {
                return GameModeName::BATTLE;
            }
            else if ( _bQuitGame.getRect().contains( mouseClick ) ) {
                return GameModeName::QUIT_GAME;
            }
        }
        return name;
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
    _title.render();

    _bNewGame.render();
    _bLoadGame.render();
    _bOptions.render();
    _bQuitGame.render();
}

GameModeName GameMode::getName() const
{
    return name;
}
