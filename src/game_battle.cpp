#include "game_battle.h"
#include "input.h"
#include "rpg_arena.h"
#include "rpg_generation.h"

ModeBattle::ModeBattle()
    : _title( { 50, 10 }, "Battle" )
    , _bExit( 400, 800, 270, 80, "Return" )
{
    name = GameModeName::BATTLE;

    RPG::Character attacker;
    RPG::Character defender;

    RPG::Force first;
    first.add( attacker );
    RPG::Force second;
    second.add( defender );
    RPG::Arena arena( first, second );
    arena.executeTurn();
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
