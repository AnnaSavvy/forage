#include "game_options.h"
#include "input.h"

ModeOptions::ModeOptions()
    : _title( { 50, 10 }, "Battle" )
    , _bExit( 400, 800, 270, 80, "Return" )
    , _realmPhysical( { 200, 200 }, { 150, 150 } )
    , _realmMagical( { 600, 200 }, { 150, 150 } )
{
    name = GameModeName::OPTIONS_SCREEN;

    std::vector<Chart::DataPoint> magicalData;
    magicalData.emplace_back( StandardColor::REALM_LIFE, 0.2 );
    magicalData.emplace_back( StandardColor::REALM_ARCANE, 0.2 );
    magicalData.emplace_back( StandardColor::REALM_DEATH, 0.2 );
    magicalData.emplace_back( StandardColor::REALM_CHAOS, 0.2 );
    magicalData.emplace_back( StandardColor::REALM_NATURE, 0.2 );
    _realmPhysical.setData( magicalData );

    std::vector<Chart::DataPoint> physicalData;
    physicalData.emplace_back( StandardColor::REALM_POWER, 0.25 );
    physicalData.emplace_back( StandardColor::REALM_DEFENSE, 0.25 );
    physicalData.emplace_back( StandardColor::REALM_SPEED, 0.25 );
    physicalData.emplace_back( StandardColor::REALM_PRECISION, 0.25 );
    _realmMagical.setData( physicalData );
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
        }
        return name;
    }
    return GameModeName::QUIT_GAME;
}

void ModeOptions::update( float deltaTime ) {}

void ModeOptions::render()
{
    _title.render();

    _realmPhysical.render();
    _realmMagical.render();

    _bExit.render();
}
