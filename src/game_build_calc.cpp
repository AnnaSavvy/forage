#include "game_build_calc.h"
#include "binding.h"
#include "character.h"
#include "input.h"
#include "renderer.h"
#include "rpg_generation.h"

#include <format>
#include <iostream>

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

    constexpr int FIRST_ROW = 30;
    constexpr int SECOND_ROW = 400;
}

ModeBuildCalculator::ModeBuildCalculator( GameState & state )
    : _state( state )
    , _title( { 0, 0, RenderEngine::GetScreenSize()._x, 50 }, "Character Builder" )
    , _bExit( RenderEngine::GetAnchorRect( AnchorPoint::BOTTOM_RIGHT, 100, 60 ).modAdd( -200, 0 ), "Return", {} )
    , _bGenerateName( RenderEngine::GetAnchorRect( AnchorPoint::BOTTOM_CENTER, 100, 60 ), "Generate", {} )
    , _bNext( RenderEngine::GetAnchorRect( AnchorPoint::BOTTOM_RIGHT, 100, 60 ), "Next >", {} )
    , _bPrevious( RenderEngine::GetAnchorRect( AnchorPoint::BOTTOM_LEFT, 100, 60 ), "< Prev", {} )
    , _health( { FIRST_ROW, 290, 236, 40 }, _character.getBinding( RPG::CharacterAttributes::HEALTH ), skillBarStyle )
    , _charName( { FIRST_ROW, 210 }, "Unknown" )
    , _levelClass( { FIRST_ROW, 250 }, "Level 1 Adventurer" )
    , _attributes( { FIRST_ROW, 350, 0, 0 } )
    , _physicalSkills( { SECOND_ROW, 80, 0, 0 } )
    , _magicalSkills( { SECOND_ROW, 350, 0, 0 } )
    , _skillPoints( { SECOND_ROW, 600 }, "Available Skill Points: " )
{
    name = GameModeName::BUILD_CALCULATOR;

    changeCharacter( _state.units.front() );

    Point p = _physicalSkills.getRect()._pos;

    for ( auto skill : physicalGroup ) {
        auto changeEvent = [this, skill]( int value ) { _character.changeAttribute( skill, value ); };
        _physicalSkills.addElement(
            std::make_shared<SkillCounter<decltype( changeEvent )> >( p, 200, RPG::Character::GetSkillName( skill ), _character.getBinding( skill ), changeEvent ) );
        p.modAdd( 0, 40 );
    }

    p = _magicalSkills.getRect()._pos;
    for ( auto skill : magicalGroup ) {
        auto changeEvent = [this, skill]( int value ) { _character.changeAttribute( skill, value ); };
        _magicalSkills.addElement(
            std::make_shared<SkillCounter<decltype( changeEvent )> >( p, 200, RPG::Character::GetSkillName( skill ), _character.getBinding( skill ), changeEvent ) );
        p.modAdd( 0, 40 );
    }

    p = _attributes.getRect()._pos;
    for ( auto attribute : attributeGroup ) {
        auto changeEvent = [this, attribute]( int value ) { _character.changeAttribute( attribute, value ); };
        _attributes.addElement( std::make_shared<AttributeCounter<decltype( changeEvent )> >( p, RPG::Character::GetSkillName( attribute ),
                                                                                              _character.getBinding( attribute ), changeEvent ) );
        p.modAdd( 0, 40 );
    }
}

void ModeBuildCalculator::changeCharacter( RPG::Character other )
{
    saveCharacter();
    _character = other;
    _charName.setText( std::format( "{}", _character.getId() ) );

    _health._binding.editValue().maximum = _character.getMaxHealth();

    const int level = _character.getBinding( RPG::CharacterAttributes::LEVEL ).value;
    _levelClass.setText( std::format( "Level {} {}", level, CharacterClassToString( _character.getClass() ) ) );

    const int sp = _character.skillPoints();
    _skillPoints.setText( std::format( "Available Skill Points: {}", sp ) );
}

void ModeBuildCalculator::saveCharacter()
{
    for ( auto & unit : _state.units ) {
        if ( unit.getId() == _character.getId() ) {
            unit = _character;
            break;
        }
    }
}

GameModeName ModeBuildCalculator::handleEvents()
{
    InputHandler & input = InputHandler::Get();

    if ( input.handleEvent() ) {
        if ( input.isSet( InputHandler::MOUSE_CLICKED ) ) {
            const Point & mouseClick = input.getClickPosition();
            if ( _bExit.getRect().contains( mouseClick ) ) {
                saveCharacter();
                return GameModeName::CANCEL;
            }
            else if ( _bGenerateName.getRect().contains( mouseClick ) ) {
                _charName.setText( RPG::Generator::GetCharacterName() );
            }
            else if ( _physicalSkills.getRect().contains( mouseClick ) ) {
                _physicalSkills.handleEvent( mouseClick, input.getModes() );
            }
            else if ( _magicalSkills.getRect().contains( mouseClick ) ) {
                _magicalSkills.handleEvent( mouseClick, input.getModes() );
            }
            else if ( _attributes.getRect().contains( mouseClick ) ) {
                _attributes.handleEvent( mouseClick, input.getModes() );
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
        else if ( input.consume( InputHandler::SPACE ) ) {
            _character.levelUp();

            const int level = _character.getBinding( RPG::CharacterAttributes::LEVEL ).value;
            _levelClass.setText( std::format( "Level {} {}", level, CharacterClassToString( _character.getClass() ) ) );

            const int sp = _character.skillPoints();
            _skillPoints.setText( std::format( "Available Skill Points: {}", sp ) );
        }
        return name;
    }
    return GameModeName::QUIT_GAME;
}

void ModeBuildCalculator::update( float deltaTime ) {}

void ModeBuildCalculator::render()
{
    _title.render();

    std::string picture = "00000.png";
    CharacterClass charClass = _character.getClass();
    switch ( charClass ) {
    case CharacterClass::MARTIAL_STR:
        picture = "00001.png";
        break;
    case CharacterClass::MAGICAL_NATURE:
        picture = "00003.png";
        break;
    case CharacterClass::MARTIAL_AGI:
        picture = "00002.png";
        break;
    default:
        break;
    }
    RenderEngine::Draw( "assets/portaits/" + picture, { FIRST_ROW, 10, 200, 300 } );

    _charName.render();
    _levelClass.render();
    _health.render();
    _bGenerateName.render();

    _attributes.render();
    _physicalSkills.render();
    _magicalSkills.render();
    _skillPoints.render();

    _bExit.render();
    _bNext.render();
    _bPrevious.render();
}
