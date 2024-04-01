#include "game_strategic.h"
#include "build_optimizer.h"
#include "input.h"
#include "renderer.h"
#include "rng.h"
#include <format>
#include <iostream>

namespace
{
    const float GATHER_TIMER = 5;
    const float SLEEP_TIMER = 4;
}

void ModeStrategicView::passTime( int amount )
{
    _state.gameTime += amount;

    const int timeInHours = _state.gameTime / 3600;
    const int hours = ( timeInHours ) % 24;

    if ( hours < 5 ) {
        RenderEngine::Get().applyTint( StandardColor::TINT_NIGHT );
    }
    else if ( hours < 9 ) {
        RenderEngine::Get().applyTint( StandardColor::TINT_MORNING );
    }
    else if ( hours > 19 ) {
        RenderEngine::Get().applyTint( StandardColor::TINT_EVENING );
    }
    else {
        RenderEngine::Get().applyTint( StandardColor::TINT_NONE );
    }
}

ModeStrategicView::ModeStrategicView( GameState & state )
    : _map( 40 )
    , _state( state )
    , _lResources( { 50, 10 }, "Food: 0, Tools: 0, Gold: 0" )
    , _bOpenMenu( RenderEngine::GetAnchorRect( AnchorPoint::TOP_RIGHT, 200, 80 ), "Menu", {} )
    , _bEndTurn( RenderEngine::GetAnchorRect( AnchorPoint::BOTTOM_RIGHT, 200, 80 ), "End Turn", {} )
    , _menuPopup( RenderEngine::GetAnchorRect( AnchorPoint::CENTER, 400, 50 ), "Menu" )
{
    name = GameModeName::NEW_GAME;

    _map.updateMap();
    _mapView.setMap( _map );
    _mapView.setPlayer( "assets/char.png" );

    _menuPopup.setHidden( true );

    Style buttonStyle{ StandardFont::REGULAR_BOLD, StandardColor::HIGHLIGHT_RED, StandardColor::BLACK, StandardColor::DARK_GREY, 5 };
    _bOpenMenu.setStyle( buttonStyle );
    _bEndTurn.setStyle( buttonStyle );
}

GameModeName ModeStrategicView::handleEvents()
{
    if ( _eventTimer > 0 ) {
        return name;
    }

    InputHandler & input = InputHandler::Get();

    if ( input.handleEvent() ) {
        if ( input.isSet( InputHandler::MOUSE_CLICKED ) ) {
            const Point & mouseClick = input.getClickPosition();
            if ( _bOpenMenu.getRect().contains( mouseClick ) ) {
                _menuPopup.setHidden( !_menuPopup.isHidden() );
            }
            else if ( _bEndTurn.getRect().contains( mouseClick ) ) {
                // trigger update
                return GameModeName::CANCEL;
            }
        }
        else if ( input.consume( InputHandler::KEY_PRESSED ) ) {
            const char key = input.consumeKey( true );
            if ( key == 'e' ) {
                _eventTimer = GATHER_TIMER;
            }
            else if ( key == 'q' ) {
                _eventTimer = SLEEP_TIMER;
            }
        }
        return name;
    }
    return GameModeName::QUIT_GAME;
}

void ModeStrategicView::update( float deltaTime )
{
    if ( _eventTimer > 0 ) {
        _eventTimer -= deltaTime;

        passTime( 12 * 60 * 60 * deltaTime / SLEEP_TIMER );
        return;
    }

    InputHandler & input = InputHandler::Get();

    // Camera update
    int xMove = input.isSet( InputHandler::RIGHT ) ? 2 : input.isSet( InputHandler::LEFT ) ? -2 : 0;
    int yMove = input.isSet( InputHandler::DOWN ) ? 2 : input.isSet( InputHandler::UP ) ? -2 : 0;
    int cameraSpeed = 2;
    if ( xMove != 0 || yMove != 0 ) {
        _scrollTimer += deltaTime;
        if ( _scrollTimer > 1.5 ) {
            cameraSpeed = ( _scrollTimer > 3 ) ? 4 : 3;
        }

        if ( _mapView.movePlayer( xMove * cameraSpeed, yMove * cameraSpeed ) ) {
            const WaveTile * tile = dynamic_cast<const WaveTile *>( _mapView.getPlayerTile() );
            if ( tile ) {
                switch ( tile->type ) {
                case WaveTile::FOREST:
                    passTime( 1800 );
                    break;
                case WaveTile::SAND:
                    passTime( 1200 );
                    break;
                default:
                    passTime( 600 );
                    break;
                }
            }

            const int timeInHours = _state.gameTime / 3600;
            const int hours = ( timeInHours ) % 24;
            const int days = timeInHours / 24;

            std::cout << std::format( "Day {} {}: Moved to next tile\n", days, hours );

            int event = RandomGenerator::Get().next( 0, 10 );
            switch ( event ) {
            case 0: {
                std::cout << std::format( "Day {} {}: Random encounter!\n", days, hours );
                break;
            }
            default:
                break;
            }
        }
    }
    else {
        _scrollTimer = 0.0f;
    }
}

void ModeStrategicView::render()
{
    _lResources.setText( std::format( "Food {}, Gold {}, Resources {}", _state.food, _state.gold, _state.resources ) );

    _mapView.render();
    _lResources.render();

    _bOpenMenu.render();
    _bEndTurn.render();

    _menuPopup.render();
}
