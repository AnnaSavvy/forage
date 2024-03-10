#include "game_build_calc.h"
#include "binding.h"
#include "character.h"
#include "input.h"
#include "renderer.h"
#include "rpg_generation.h"

namespace
{
    const std::vector<RPG::Character::Skills> martialGroup
        = { RPG::Character::CLOSE_COMBAT, RPG::Character::RANGED_COMBAT, RPG::Character::DODGE, RPG::Character::BLOCK, RPG::Character::STEALTH };
    const std::vector<RPG::Character::Skills> magicalGroup
        = { RPG::Character::LIFE, RPG::Character::ARCANA, RPG::Character::NATURE, RPG::Character::CHAOS, RPG::Character::DEATH };

    const Style skillBarStyle{ StandardFont::SMALL, StandardColor::WHITE, StandardColor::DARK_GREY, StandardColor::REALM_PRECISION, 2 };

    constexpr int FIRST_ROW = 20;
    constexpr int SECOND_ROW = 300;

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

            addElement( std::make_shared<ProgressBar>( ProgressBar( { position._x, position._y, width, 31 }, binding, skillBarStyle ) ) );

            const Style buttonStyle{ StandardFont::REGULAR, StandardColor::WHITE, StandardColor::DARK_GREY, StandardColor::REALM_PRECISION, 2 };

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
    , _bGenerateName( RenderEngine::GetScreenSize()._x / 2 - 100, RenderEngine::GetScreenSize()._y - 80, 100, 60, "Generate" )
    , _bNext( RenderEngine::GetScreenSize()._x - 110, RenderEngine::GetScreenSize()._y - 80, 100, 60, "Next >" )
    , _bPrevious( FIRST_ROW, RenderEngine::GetScreenSize()._y - 80, 100, 60, "< Prev" )
    , _health( { FIRST_ROW, 490, 236, 40 }, _character.getSkillBinding( RPG::Character::ARCANA ), skillBarStyle )
    , _charName( { FIRST_ROW, 410 }, "Unknown" )
    , _levelClass( { FIRST_ROW, 440 }, "Level 1 Adventurer" )
    , _attributes( { FIRST_ROW, 550, 0, 0 } )
    , _physicalSkills( { SECOND_ROW, 200, 0, 0 } )
    , _magicalSkills( { SECOND_ROW, 500, 0, 0 } )
{
    name = GameModeName::BUILD_CALCULATOR;

    Point p = _physicalSkills.getRect()._pos;

    for ( auto skill : martialGroup ) {
        _physicalSkills.addElement( std::make_shared<SkillCounter>( p, 200, skill, _character.getSkillBinding( skill ) ) );
        p.modAdd( 0, 40 );
    }

    p = _magicalSkills.getRect()._pos;
    for ( auto skill : magicalGroup ) {
        _magicalSkills.addElement( std::make_shared<SkillCounter>( p, 200, skill, _character.getSkillBinding( skill ) ) );
        p.modAdd( 0, 40 );
    }
}

void ModeBuildCalculator::changeCharacter( RPG::Character other )
{
    _character = other;
    _charName.setText( std::to_string( _character.getId() ) );
    _levelClass.setText( "Level 1 " + ToString( _character.getClass() ) );
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
            else if ( _physicalSkills.getRect().contains( mouseClick ) ) {
                _physicalSkills.handleClickEvent( mouseClick, input.getModes() & InputHandler::MOUSE_CLICKED );
            }
            else if ( _magicalSkills.getRect().contains( mouseClick ) ) {
                _magicalSkills.handleClickEvent( mouseClick, input.getModes() & InputHandler::MOUSE_CLICKED );
            }
            else if ( _attributes.getRect().contains( mouseClick ) ) {
                _attributes.handleClickEvent( mouseClick, input.getModes() & InputHandler::MOUSE_CLICKED );
            }
            else if ( _bNext.getRect().contains( mouseClick ) ) {
                for ( auto it = _state.units.begin(); it != _state.units.end(); ++it ) {
                    if ( it->getId() == _character.getId() ) {
                        it++;
                        if ( it != _state.units.end() ) {
                            changeCharacter( *it );
                        }
                        break;
                    }
                }
            }
            else if ( _bPrevious.getRect().contains( mouseClick ) ) {
                for ( auto it = _state.units.begin(); it != _state.units.end(); ++it ) {
                    if ( it->getId() == _character.getId() ) {
                        if ( it != _state.units.begin() ) {
                            it--;
                            changeCharacter( *it );
                        }
                        break;
                    }
                }
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

    RenderEngine::Draw( "assets/portaits/03087.png", { 10, 10, 256, 384 } );

    _charName.render();
    _levelClass.render();
    _health.render();
    _bGenerateName.render();

    _attributes.render();
    _physicalSkills.render();
    _magicalSkills.render();

    _bExit.render();
    _bNext.render();
    _bPrevious.render();
}
