#include "game_build_calc.h"
#include "input.h"
#include "rpg_generation.h"

ModeBuildCalculator::ModeBuildCalculator()
    : _title( { 50, 10 }, "Character Builer" )
    , _bExit( 400, 800, 270, 80, "Return" )
    , _charName( { 50, 80 }, "Unknown" )
    , _bGenerateName( 50, 130, 100, 50, "Generate" )
{
    name = GameModeName::BUILD_CALCULATOR;
}

GameModeName ModeBuildCalculator::handleEvents()
{
    InputHandler & input = InputHandler::Get();

    if ( input.handleEvent() ) {
        if ( input.isSet( InputHandler::MOUSE_CLICKED ) ) {
            const Point & mouseClick = input.getClickPosition();
            if ( _bExit.getRect().contains( mouseClick ) ) {
                return GameModeName::CANCEL;
            }
            else if ( _bGenerateName.getRect().contains( mouseClick ) ) {
                _charName.setText( RPG::Generator::GetCharacterName() );
            }
        }
        return name;
    }
    return GameModeName::QUIT_GAME;
}

void ModeBuildCalculator::update( float deltaTime ) {}

void ModeBuildCalculator::render()
{
    _title.render();
    _bExit.render();

    _charName.render();
    _bGenerateName.render();
}
