#include "game_strategic.h"
#include "input.h"
#include "renderer.h"

ModeStrategicView::ModeStrategicView()
    : _map( 40 )
    , _lResources( { 50, 10 }, "Food: 0, Tools: 0, Gold: 0" )
    , _bOpenMenu( 824, 10, 200, 80, "Menu" )
    , _bEndTurn( 824, 944, 200, 80, "End Turn" )
{
    name = GameModeName::NEW_GAME;

    _map.updateMap();
    _mapView.setMap( _map );

    Style buttonStyle;
    buttonStyle.font = StandardFont::REGULAR_BOLD;
    buttonStyle.textColor = StandardColor::HIGHLIGHT_RED;
    buttonStyle.borderColor = StandardColor::DARK_GREY;
    buttonStyle.borderWidth = 5;
    _bOpenMenu.setStyle( buttonStyle );
    _bEndTurn.setStyle( buttonStyle );
}

GameModeName ModeStrategicView::handleEvents()
{
    InputHandler & input = InputHandler::Get();

    if ( input.handleEvent() ) {
        if ( input.isSet( InputHandler::MOUSE_CLICKED ) ) {
            const Point & mouseClick = input.getClickPosition();
            if ( _bOpenMenu.getRect().contains( mouseClick ) ) {
                return GameModeName::MAIN_MENU;
                // pop up menu Window
            }
            else if ( _bEndTurn.getRect().contains( mouseClick ) ) {
                // trigger update
            }
        }
        return name;
    }
    return GameModeName::QUIT_GAME;
}

void ModeStrategicView::update( float deltaTime )
{
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
        _mapView.moveCamera( xMove * cameraSpeed, yMove * cameraSpeed );
    }
    else {
        _scrollTimer = 0.0f;
    }
}

void ModeStrategicView::render()
{
    _mapView.render();
    _lResources.render();

    _bOpenMenu.render();
    _bEndTurn.render();
}
