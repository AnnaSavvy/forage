#include "game_options.h"
#include "character.h"
#include "input.h"
#include "renderer.h"

ModeOptions::ModeOptions()
    : _title( { 0, 0, RenderEngine::GetScreenSize()._x, 50 }, "Options" )
    , _bExit( RenderEngine::GetAnchorRect( AnchorPoint::BOTTOM_RIGHT, 270, 80 ), "Return", {} )
    , _realmPhysical( { 150, 150 }, { 300, 300 } )
    , _realmMagical( { 600, 150 }, { 300, 300 } )
{
    name = GameModeName::OPTIONS_SCREEN;

    std::vector<Chart::DataPoint> physicalData;
    physicalData.emplace_back( StandardColor::REALM_POWER, 0.25 );
    physicalData.emplace_back( StandardColor::REALM_PRECISION, 0.25 );
    physicalData.emplace_back( StandardColor::REALM_SPEED, 0.25 );
    physicalData.emplace_back( StandardColor::REALM_DEFENSE, 0.25 );
    _realmPhysical.setData( physicalData );

    std::vector<Chart::DataPoint> magicalData;
    magicalData.emplace_back( StandardColor::REALM_LIFE, 0.2 );
    magicalData.emplace_back( StandardColor::REALM_ARCANE, 0.2 );
    magicalData.emplace_back( StandardColor::REALM_DEATH, 0.2 );
    magicalData.emplace_back( StandardColor::REALM_CHAOS, 0.2 );
    magicalData.emplace_back( StandardColor::REALM_NATURE, 0.2 );
    _realmMagical.setData( magicalData );
}

GameModeName ModeOptions::handleEvents()
{
    InputHandler & input = InputHandler::Get();

    if ( input.handleEvent() ) {
        if ( input.isSet( InputHandler::MOUSE_CLICKED ) ) {
            const Point & mouseClick = input.getClickPosition();
            if ( _bExit.getRect().contains( mouseClick ) ) {
                return GameModeName::CANCEL;
            }
            else if ( _realmPhysical.getRect().contains( mouseClick ) ) {
                _realmPhysical.handleClick( mouseClick );
            }
            else if ( _realmMagical.getRect().contains( mouseClick ) ) {
                _realmMagical.handleClick( mouseClick );
            }
        }
        else if ( input.isSet( InputHandler::UP ) ) {
            if ( inputDelay <= 0 ) {
                current = static_cast<CharacterClass>( static_cast<int>( current ) + 1 );
                _title.setText( CharacterClassToString( current ) );
                pick( current );
                inputDelay = 15;
            }
            inputDelay--;
        }
        else if ( input.isSet( InputHandler::DOWN ) ) {
            if ( inputDelay <= 0 ) {
                current = static_cast<CharacterClass>( static_cast<int>( current ) - 1 );
                _title.setText( CharacterClassToString( current ) );
                pick( current );
                inputDelay = 15;
            }
            inputDelay--;
        }
        return name;
    }
    return GameModeName::QUIT_GAME;
}

void ModeOptions::update( float deltaTime )
{
    _realmPhysical.update( deltaTime );
    _realmMagical.update( deltaTime );
}

void ModeOptions::render()
{
    _title.render();

    _realmPhysical.render();
    _realmMagical.render();

    _bExit.render();
}

void ModeOptions::pick( CharacterClass name )
{
    Requirements require = Requirements::BuildForClass( name );

    for ( Chart::DataPoint & dp : _realmPhysical.getData() ) {
        switch ( dp.color ) {
        case StandardColor::REALM_POWER:
            dp.active = require.stat.strength >= 50;
            break;
        case StandardColor::REALM_PRECISION:
            dp.active = require.stat.dexterity >= 50;
            break;
        case StandardColor::REALM_SPEED:
            dp.active = require.stat.agility >= 50;
            break;
        case StandardColor::REALM_DEFENSE:
            dp.active = require.stat.constitution >= 50;
            break;
        }
    }

    for ( Chart::DataPoint & dp : _realmMagical.getData() ) {
        switch ( dp.color ) {
        case StandardColor::REALM_LIFE:
            dp.active = require.skill.life >= 50;
            break;
        case StandardColor::REALM_ARCANE:
            dp.active = require.skill.sorcery >= 50;
            break;
        case StandardColor::REALM_NATURE:
            dp.active = require.skill.nature >= 50;
            break;
        case StandardColor::REALM_CHAOS:
            dp.active = require.skill.chaos >= 50;
            break;
        case StandardColor::REALM_DEATH:
            dp.active = require.skill.death >= 50;
            break;
        }
    }
}
