#include "game_battle.h"
#include "input.h"

ModeBattle::ModeBattle()
    : _title( { 50, 10 }, "Battle" )
    , _bExit( 400, 800, 270, 80, "Return" )
{
    name = GameModeName::BATTLE;
}

GameModeName ModeBattle::handleEvents()
{
    InputHandler & input = InputHandler::Get();

    if ( input.handleEvent() ) {
        if ( input.isSet( InputHandler::MOUSE_CLICKED ) ) {
            const Point & mouseClick = input.getClickPosition();
            if ( _bExit.getRect().contains( mouseClick ) ) {
                return GameModeName::CANCEL;
            }
        }
        return name;
    }
    return GameModeName::QUIT_GAME;
}

void ModeBattle::update( float deltaTime ) {}

void ModeBattle::render()
{
    _title.render();

    _bExit.render();
}
