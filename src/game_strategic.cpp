#include "game_strategic.h"
#include "build_optimizer.h"
#include "input.h"
#include "renderer.h"
#include <iostream>

ModeStrategicView::ModeStrategicView()
    : _map( 40 )
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
            std::cout << "Moved" << std::endl;
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
