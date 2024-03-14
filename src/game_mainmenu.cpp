#include "game_mainmenu.h"
#include "chart.h"
#include "input.h"
#include "renderer.h"

namespace
{
    const Style buttonStyle{ StandardFont::REGULAR_BOLD, StandardColor::HIGHLIGHT_RED, StandardColor::BLACK, StandardColor::DARK_GREY, 5 };
}

ModeMainMenu::ModeMainMenu()
    : _backgroundMap( 100 )
    , _mapView( true )
    , _title( RenderEngine::GetAnchorPoint( AnchorPoint::TOP_CENTER ).modAdd( -333, 80 ), "Best Damn Game", StandardFont::MENU_HUGE_TITLE, StandardColor::WHITE )
    , _bNewGame( RenderEngine::GetAnchorRect( AnchorPoint::CENTER, 270, 80 ), "New Game", buttonStyle )
    , _bLoadGame( RenderEngine::GetAnchorPoint( AnchorPoint::CENTER, 270, 80 ).modAdd( 0, 100 ), 270, 80, "Load Game", buttonStyle )
    , _bOptions( RenderEngine::GetAnchorPoint( AnchorPoint::CENTER, 270, 80 ).modAdd( 0, 200 ), 270, 80, "Options", buttonStyle )
    , _bQuitGame( RenderEngine::GetAnchorPoint( AnchorPoint::CENTER, 270, 80 ).modAdd( 0, 300 ), 270, 80, "Quit Game", buttonStyle )
{
    name = GameModeName::MAIN_MENU;

    _backgroundMap.updateMap();
    _mapView.setMap( _backgroundMap );
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
