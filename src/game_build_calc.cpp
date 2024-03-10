#include "game_build_calc.h"
#include "binding.h"
#include "character.h"
#include "input.h"
#include "renderer.h"
#include "rpg_generation.h"

namespace
{
    const std::vector<RPG::Character::Skills> group
        = { RPG::Character::CLOSE_COMBAT, RPG::Character::RANGED_COMBAT, RPG::Character::DODGE, RPG::Character::BLOCK, RPG::Character::STEALTH };

    class SkillCounter : public UIContainer
    {
        ValueBinding _binding;

    public:
        SkillCounter( Point position, int width, RPG::Character::Skills skill, ValueBinding binding )
            : UIContainer( { position._x, position._y, 0, 0 } )
            , _binding( binding )
        {
            addElement( std::make_shared<Label>( Label( position, RPG::Character::GetSkillName( skill ) ) ) );
            position.modAdd( 150, 0 );

            Style skillBarStyle;
            skillBarStyle.font = StandardFont::SMALL;
            skillBarStyle.textColor = StandardColor::WHITE;
            skillBarStyle.backgroundColor = StandardColor::DARK_GREY;
            skillBarStyle.borderColor = StandardColor::REALM_PRECISION;
            skillBarStyle.borderWidth = 2;
            skillBarStyle.borderRadius = 5;

            addElement( std::make_shared<ProgressBar>( ProgressBar( { position._x, position._y, width, 31 }, binding, skillBarStyle ) ) );

            Style buttonStyle;
            buttonStyle.font = StandardFont::REGULAR;
            buttonStyle.textColor = StandardColor::WHITE;
            buttonStyle.backgroundColor = StandardColor::DARK_GREY;
            buttonStyle.borderColor = StandardColor::REALM_PRECISION;
            buttonStyle.borderWidth = 2;

            addElement( std::make_shared<Button>( Button( { position._x + width + 5, position._y, 31, 31 }, "+", buttonStyle ) ) );
            addElement( std::make_shared<Button>( Button( { position._x - 36, position._y, 31, 31 }, "-", buttonStyle ) ) );

            updateRect();
        }

        void handleClickEvent( const Point & click, int modes ) override
        {
            if ( _items[2]->getRect().contains( click ) ) {
                const int change = modes & InputHandler::MOUSE_RIGHT_CLICKED ? 10 : 1;
                _binding.value = std::min( _binding.value + change, _binding.maximum );
            }
            else if ( _items[3]->getRect().contains( click ) ) {
                const int change = modes & InputHandler::MOUSE_RIGHT_CLICKED ? 10 : 1;
                _binding.value = std::min( _binding.value - change, _binding.maximum );
            }
        }
    };
}

ModeBuildCalculator::ModeBuildCalculator( GameState & state )
    : _state( state )
    , _character( _state.units.front() )
    , _title( { 50, 10 }, "Character Builer" )
    , _bExit( RenderEngine::GetScreenSize()._x / 2 + 100, RenderEngine::GetScreenSize()._y - 80, 270, 60, "Return" )
    , _charName( { RenderEngine::GetScreenSize()._x / 2, 80 }, "Unknown" )
    , _bGenerateName( RenderEngine::GetScreenSize()._x / 2 - 100, RenderEngine::GetScreenSize()._y - 80, 100, 60, "Generate" )
    , skills( { 300, 500, 0, 0 } )
{
    name = GameModeName::BUILD_CALCULATOR;

    Point p = skills.getRect()._pos;

    for ( auto skill : group ) {
        skills.addElement( std::make_shared<SkillCounter>( p, 200, skill, _character.getSkillBinding( skill ) ) );
        p.modAdd( 0, 40 );
    }
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
            else if ( skills.getRect().contains( mouseClick ) ) {
                skills.handleClickEvent( mouseClick, input.getModes() & InputHandler::MOUSE_CLICKED );
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

    skills.render();
}
