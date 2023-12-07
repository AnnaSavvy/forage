#include "game_build_calc.h"
#include "input.h"
#include "rpg_generation.h"
#include "renderer.h"

ModeBuildCalculator::ModeBuildCalculator()
    : _title( { 50, 10 }, "Character Builer" )
    , _bExit( 400, 800, 270, 80, "Return" )
    , _charName( { RenderEngine::GetScreenSize()._x / 2, 80 }, "Unknown" )
    , _bGenerateName( RenderEngine::GetScreenSize()._x / 2, 130, 100, 50, "Generate" )
{
    name = GameModeName::BUILD_CALCULATOR;

    Style skillBarStyle;
    skillBarStyle.font = StandardFont::SMALL;
    skillBarStyle.textColor = StandardColor::WHITE;
    skillBarStyle.backgroundColor = StandardColor::DARK_GREY;
    skillBarStyle.borderColor = StandardColor::REALM_PRECISION;
    skillBarStyle.borderWidth = 2;
    skillBarStyle.borderRadius = 5;

    Style buttonStyle;
    buttonStyle.font = StandardFont::REGULAR;
    buttonStyle.textColor = StandardColor::WHITE;
    buttonStyle.backgroundColor = StandardColor::DARK_GREY;
    buttonStyle.borderColor = StandardColor::REALM_PRECISION;
    buttonStyle.borderWidth = 2;


    increase.push_back( { { 264, 200, 31, 31 }, "-", buttonStyle } );
    skills.push_back( { { 300, 200, 200, 31 }, 100, skillBarStyle } );
    increase.push_back( { { 505, 200, 31, 31 }, "+", buttonStyle } );

    skills.push_back( { { 300, 250, 200, 31 }, 100, skillBarStyle } );
    skills.push_back( { { 300, 300, 200, 31 }, 100, skillBarStyle } );
    skills.push_back( { { 300, 350, 200, 31 }, 100, skillBarStyle } );
    skills.push_back( { { 300, 400, 200, 31 }, 100, skillBarStyle } );
    skills.push_back( { { 300, 450, 200, 31 }, 100, skillBarStyle } );
    skills.push_back( { { 300, 500, 200, 31 }, 100, skillBarStyle } );
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
            else if ( increase[0].getRect().contains( mouseClick ) ) {
                skills[0].setValue( skills[0].getValue() - 1 );
            }
            else if ( increase[1].getRect().contains( mouseClick ) ) {
                skills[0].setValue( skills[0].getValue() + 1 );
            }
        }
        else if ( input.isSet( InputHandler::UP ) ) {
            skills[0].setValue( skills[0].getValue() + 1 );
        }
        else if ( input.isSet( InputHandler::DOWN ) ) {
            if ( skills[0].getValue() > 0 ) {
                skills[0].setValue( skills[0].getValue() - 1 );
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

    RenderEngine::Draw( "assets/portaits/03087.png", { 10, 10, 256, 384 } );

    _charName.render();
    _bGenerateName.render();

    for ( auto & elem : skills ) {
        elem.render();
    }
    for ( auto & elem : increase ) {
        elem.render();
    }
}
