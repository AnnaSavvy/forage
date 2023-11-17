#include "game_options.h"
#include "input.h"

ModeOptions::ModeOptions()
    : _title( { 50, 10 }, "Options" )
    , _bExit( 400, 800, 270, 80, "Return" )
    , _realmPhysical( { 200, 200 }, { 150, 150 } )
    , _realmMagical( { 600, 200 }, { 150, 150 } )
{
    name = GameModeName::OPTIONS_SCREEN;

    std::vector<Chart::DataPoint> physicalData;
    physicalData.emplace_back( StandardColor::REALM_POWER, 0.25 );
    physicalData.emplace_back( StandardColor::REALM_PRECISION, 0.25 );
    physicalData.emplace_back( StandardColor::REALM_SPEED, 0.25 );
    physicalData.emplace_back( StandardColor::REALM_DEFENSE, 0.25 );
    _realmPhysical.setData( physicalData );

    std::vector<Chart::DataPoint> magicalData;
    magicalData.emplace_back( StandardColor::REALM_LIFE, 0.2, false );
    magicalData.emplace_back( StandardColor::REALM_ARCANE, 0.2, false );
    magicalData.emplace_back( StandardColor::REALM_DEATH, 0.2, false );
    magicalData.emplace_back( StandardColor::REALM_CHAOS, 0.2, false );
    magicalData.emplace_back( StandardColor::REALM_NATURE, 0.2, false );
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
            else if ( _realmMagical.getRect().contains(mouseClick ) ) {
                _realmMagical.handleClick( mouseClick );
            }
        }
        return name;
    }
    return GameModeName::QUIT_GAME;
}

void ModeOptions::update( float deltaTime ) {
    _realmMagical.update( deltaTime );
}

void ModeOptions::render()
{
    _title.render();

    _realmMagical.render();
    _realmPhysical.render();

    _bExit.render();
}
