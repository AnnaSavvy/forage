#include "game_strategic.h"
#include "build_optimizer.h"
#include "input.h"
#include "renderer.h"
#include "rng.h"
#include <format>
#include <iostream>

ModeStrategicView::ModeStrategicView( GameState & state )
    : _map( 40 )
    , _state( state )
    , _lResources( { 50, 10 }, "Food: 0, Tools: 0, Gold: 0" )
    , _bOpenMenu( RenderEngine::GetAnchorRect( AnchorPoint::TOP_RIGHT, 200, 80 ), "Menu", {} )
    , _bEndTurn( RenderEngine::GetAnchorRect( AnchorPoint::BOTTOM_RIGHT, 200, 80 ), "End Turn", {} )
    , _menuPopup( RenderEngine::GetAnchorRect( AnchorPoint::CENTER, 400, 50 ), "Menu" )
{
    name = GameModeName::NEW_GAME;

    _map.updateMap();
    _mapView.setMap( _map );
    _mapView.setPlayer( "assets/char.png" );

    _menuPopup.setHidden( true );

    Style buttonStyle{ StandardFont::REGULAR_BOLD, StandardColor::HIGHLIGHT_RED, StandardColor::BLACK, StandardColor::DARK_GREY, 5 };
    _bOpenMenu.setStyle( buttonStyle );
    _bEndTurn.setStyle( buttonStyle );

    BuildOrder::City city;
    city.landPopulation = 24;
    city.landProduction = 27;
    city.landGold = 30;
    city.racialGrowth = -2;
    city.taxCollectionMode = 3;
    city.population = 1;

    city.buildings = { BuildOrder::Builders, BuildOrder::Granary };

    std::vector<BuildOrder::Building> buildOrder1
        = { BuildOrder::Smithy,     BuildOrder::Marketplace,  BuildOrder::Farmers,   BuildOrder::Shrine,     BuildOrder::Library,   BuildOrder::Sages,
            BuildOrder::University, BuildOrder::Sawmill,      BuildOrder::Foresters, BuildOrder::Temple,     BuildOrder::Parthenon, BuildOrder::Miners,
            BuildOrder::Bank,       BuildOrder::Mechanicians, BuildOrder::Cathedral, BuildOrder::Alchemists, BuildOrder::Wizards };

    std::vector<BuildOrder::Building> buildOrder2
        = { BuildOrder::Sawmill, BuildOrder::Smithy,    BuildOrder::Marketplace, BuildOrder::Farmers,    BuildOrder::Foresters,    BuildOrder::Miners,
            BuildOrder::Shrine,  BuildOrder::Library,   BuildOrder::Sages,       BuildOrder::University, BuildOrder::Mechanicians, BuildOrder::Bank,
            BuildOrder::Temple,  BuildOrder::Parthenon, BuildOrder::Cathedral,   BuildOrder::Alchemists, BuildOrder::Wizards };

    std::vector<BuildOrder::Building> buildOrder3
        = { BuildOrder::Smithy,     BuildOrder::Marketplace,  BuildOrder::Farmers, BuildOrder::Sawmill,   BuildOrder::Foresters,
            BuildOrder::Miners,     BuildOrder::Shrine,       BuildOrder::Library, BuildOrder::Sages,     BuildOrder::University,
            BuildOrder::Temple,     BuildOrder::Mechanicians, BuildOrder::Bank,    BuildOrder::Parthenon, BuildOrder::Cathedral,
            BuildOrder::Alchemists, BuildOrder::Wizards,      BuildOrder::Armory,  BuildOrder::Stables,   BuildOrder::Animists };

    BuildOrder::Optimizer optimizer;
    optimizer.PrintResult( optimizer.executeBuildOrder( city, buildOrder1 ) );

    optimizer.PrintResult( optimizer.executeBuildOrder( city, buildOrder2 ) );

    optimizer.PrintFullHistory( optimizer.executeBuildOrder( city, buildOrder3 ) );
}

GameModeName ModeStrategicView::handleEvents()
{
    InputHandler & input = InputHandler::Get();

    if ( input.handleEvent() ) {
        if ( input.isSet( InputHandler::MOUSE_CLICKED ) ) {
            const Point & mouseClick = input.getClickPosition();
            if ( _bOpenMenu.getRect().contains( mouseClick ) ) {
                _menuPopup.setHidden( !_menuPopup.isHidden() );
            }
            else if ( _bEndTurn.getRect().contains( mouseClick ) ) {
                // trigger update
                return GameModeName::CANCEL;
            }
        }
        return name;
    }
    return GameModeName::QUIT_GAME;
}

void ModeStrategicView::update( float deltaTime )
{
    InputHandler & input = InputHandler::Get();

    // Camera update
    int xMove = input.isSet( InputHandler::RIGHT ) ? 2 : input.isSet( InputHandler::LEFT ) ? -2 : 0;
    int yMove = input.isSet( InputHandler::DOWN ) ? 2 : input.isSet( InputHandler::UP ) ? -2 : 0;
    int cameraSpeed = 2;
    if ( xMove != 0 || yMove != 0 ) {
        _scrollTimer += deltaTime;
        if ( _scrollTimer > 1.5 ) {
            cameraSpeed = ( _scrollTimer > 3 ) ? 4 : 3;
        }

        if ( _mapView.movePlayer( xMove * cameraSpeed, yMove * cameraSpeed ) ) {
            const WaveTile * tile = dynamic_cast<const WaveTile *>( _mapView.getPlayerTile() );
            if ( tile ) {
                switch ( tile->type ) {
                case WaveTile::FOREST:
                    _state.gameTime += 1800;
                    break;
                case WaveTile::SAND:
                    _state.gameTime += 1200;
                    break;
                default:
                    _state.gameTime += 600;
                    break;
                }
            }

            const int timeInHours = _state.gameTime / 3600;
            const int hours = ( timeInHours ) % 24;
            const int days = timeInHours / 24;

            std::cout << std::format( "Day {} {}: Moved to next tile\n", days, hours );
            if ( hours < 5 ) {
                RenderEngine::Get().applyTint( StandardColor::TINT_NIGHT );
            }
            else if ( hours < 9 ) {
                RenderEngine::Get().applyTint( StandardColor::TINT_MORNING );
            }
            else if ( hours > 19 ) {
                RenderEngine::Get().applyTint( StandardColor::TINT_EVENING );
            }
            else {
                RenderEngine::Get().applyTint( StandardColor::TINT_NONE );
            }

            int event = RandomGenerator::Get().next( 0, 10 );
            switch ( event ) {
            case 0: {
                std::cout << std::format( "Day {} {}: Random encounter!\n", days, hours );
                break;
            }
            default:
                break;
            }
        }
    }
    else {
        _scrollTimer = 0.0f;
    }
}

void ModeStrategicView::render()
{
    _mapView.render();
    _lResources.render();

    _bOpenMenu.render();
    _bEndTurn.render();

    _menuPopup.render();
}
