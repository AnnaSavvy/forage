#include "game_build_calc.h"
#include "binding.h"
#include "character.h"
#include "input.h"
#include "renderer.h"
#include "rpg_generation.h"
#include "ui_rpg.h"

namespace
{
    const std::vector<RPG::CharacterAttributes> attributeGroup
        = { RPG::CharacterAttributes::STRENGTH,     RPG::CharacterAttributes::AGILITY,   RPG::CharacterAttributes::CONSTITUTION, RPG::CharacterAttributes::DEXTERITY,
            RPG::CharacterAttributes::INTELLIGENCE, RPG::CharacterAttributes::WILLPOWER, RPG::CharacterAttributes::CHARISMA };
    const std::vector<RPG::CharacterAttributes> physicalGroup = { RPG::CharacterAttributes::CLOSE_COMBAT, RPG::CharacterAttributes::RANGED_COMBAT,
                                                                  RPG::CharacterAttributes::DODGE, RPG::CharacterAttributes::BLOCK, RPG::CharacterAttributes::STEALTH };
    const std::vector<RPG::CharacterAttributes> magicalGroup = { RPG::CharacterAttributes::LIFE, RPG::CharacterAttributes::ARCANA, RPG::CharacterAttributes::NATURE,
                                                                 RPG::CharacterAttributes::CHAOS, RPG::CharacterAttributes::DEATH };

    const Style skillBarStyle{ StandardFont::SMALL, StandardColor::WHITE, StandardColor::DARK_GREY, StandardColor::REALM_PRECISION, 2 };

    constexpr int FIRST_ROW = 20;
    constexpr int SECOND_ROW = 300;
}

ModeBuildCalculator::ModeBuildCalculator( GameState & state )
    : _state( state )
    , _title( { 50, 10 }, "Character Builer" )
    , _bExit( RenderEngine::GetScreenSize()._x / 2 + 100, RenderEngine::GetScreenSize()._y - 80, 270, 60, "Return" )
    , _bGenerateName( RenderEngine::GetScreenSize()._x / 2 - 100, RenderEngine::GetScreenSize()._y - 80, 100, 60, "Generate" )
    , _bNext( RenderEngine::GetScreenSize()._x - 110, RenderEngine::GetScreenSize()._y - 80, 100, 60, "Next >" )
    , _bPrevious( FIRST_ROW, RenderEngine::GetScreenSize()._y - 80, 100, 60, "< Prev" )
    , _health( { FIRST_ROW, 480, 236, 40 }, _character.getBinding( RPG::CharacterAttributes::HEALTH ), skillBarStyle )
    , _charName( { FIRST_ROW, 410 }, "Unknown" )
    , _levelClass( { FIRST_ROW, 440 }, "Level 1 Adventurer" )
    , _attributes( { FIRST_ROW, 580, 0, 0 } )
    , _physicalSkills( { SECOND_ROW, 200, 0, 0 } )
    , _magicalSkills( { SECOND_ROW, 500, 0, 0 } )
{
    name = GameModeName::BUILD_CALCULATOR;

    changeCharacter( _state.units.front() );

    Point p = _physicalSkills.getRect()._pos;

    for ( auto skill : physicalGroup ) {
        _physicalSkills.addElement( std::make_shared<SkillCounter>( p, 200, RPG::Character::GetSkillName( skill ), _character.getBinding( skill ) ) );
        p.modAdd( 0, 40 );
    }

    p = _magicalSkills.getRect()._pos;
    for ( auto skill : magicalGroup ) {
        _magicalSkills.addElement( std::make_shared<SkillCounter>( p, 200, RPG::Character::GetSkillName( skill ), _character.getBinding( skill ) ) );
        p.modAdd( 0, 40 );
    }

    p = _attributes.getRect()._pos;
    for ( auto attribute : attributeGroup ) {
        _attributes.addElement( std::make_shared<AttributeCounter>( p, RPG::Character::GetSkillName( attribute ), _character.getBinding( attribute ) ) );
        p.modAdd( 0, 40 );
    }
}

void ModeBuildCalculator::changeCharacter( RPG::Character other )
{
    _character = other;
    _charName.setText( std::to_string( _character.getId() ) );

    _health._binding.editValue().maximum = _character.getMaxHealth();

    const int level = _character.getBinding( RPG::CharacterAttributes::LEVEL ).value;
    _levelClass.setText( "Level " + std::to_string( level ) + " " + CharacterClassToString( _character.getClass() ) );
}

GameModeName ModeBuildCalculator::handleEvents()
{
    InputHandler & input = InputHandler::Get();

    if ( input.handleEvent() ) {
        if ( input.isSet( InputHandler::MOUSE_CLICKED ) ) {
            const Point & mouseClick = input.getClickPosition();
            if ( _bExit.getRect().contains( mouseClick ) ) {
                for ( auto & unit : _state.units ) {
                    if ( unit.getId() == _character.getId() ) {
                        unit = _character;
                        break;
                    }
                }
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
