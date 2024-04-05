#include "game_strategic.h"
#include "build_optimizer.h"
#include "input.h"
#include "renderer.h"
#include "rng.h"

#include <SDL_scancode.h>
#include <format>
#include <iostream>

namespace
{
    const float GATHER_TIMER = 6;
    const float SLEEP_TIMER = 4;
}

void ModeStrategicView::passTime( int amount )
{
    _state.gameTime += amount;

    const int timeInHours = _state.gameTime / 3600;
    const int hours = ( timeInHours ) % 24;

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
}

void ModeStrategicView::executeEvent( float deltaTime )
{
    _eventTimer -= deltaTime;

    if ( _eventType == MapEventType::SLEEP ) {
        passTime( 12 * 60 * 60 * deltaTime / SLEEP_TIMER );
    }
    else if ( _eventType == MapEventType::GATHERING ) {
        passTime( 12 * 60 * 60 * deltaTime / GATHER_TIMER );
        _eventSubtimer += deltaTime;

        const int basedOnSkill = 10;
        const float subtimer = GATHER_TIMER / basedOnSkill;
        if ( _eventSubtimer > subtimer ) {
            _eventSubtimer -= subtimer;
            _state.food++;
            temporaryUI.addElement( std::make_shared<FlyingText>( RenderEngine::GetScreenSize().modDiv( 2 ).add( 40, 0 ), "+1", 3 ) );
        }
    }
}

ModeStrategicView::ModeStrategicView( GameState & state )
    : _map( 40 )
    , _state( state )
    , _lResources( { 50, 10 }, "Food: 0, Tools: 0, Gold: 0" )
    , _bOpenMenu( RenderEngine::GetAnchorRect( AnchorPoint::TOP_RIGHT, 200, 80 ), "Menu", {} )
    , _bEndTurn( RenderEngine::GetAnchorRect( AnchorPoint::BOTTOM_RIGHT, 200, 80 ), "End Turn", {} )
    , _menuPopup( RenderEngine::GetAnchorRect( AnchorPoint::CENTER, 400, 50 ), "Menu" )
    , temporaryUI( {} )
    , encounterWindow( dialog )
{
    name = GameModeName::NEW_GAME;

    _map.updateMap();
    _mapView.setMap( _map );
    _mapView.setPlayer( "assets/char.png" );

    _menuPopup.setHidden( true );

    Style buttonStyle{ StandardFont::REGULAR_BOLD, StandardColor::HIGHLIGHT_RED, StandardColor::BLACK, StandardColor::DARK_GREY, 5 };
    _bOpenMenu.setStyle( buttonStyle );
    _bEndTurn.setStyle( buttonStyle );

    dialog.root.text = "The party stumbles upon a group of goblins raiding a nearby village or caravan.";

    DialogOption option1;
    option1.description = "Option 1. Check STR";
    option1.goodOutcome = std::make_unique<DialogNode>();
    option1.goodOutcome->reward.value = 10;
    option1.goodOutcome->text = "Good job! You passed STR check!";
    dialog.root.options.push_back( std::move( option1 ) );

    DialogOption option2;
    option2.description = "Option 2. Check CHA";
    option2.goodOutcome = std::make_unique<DialogNode>();
    option2.goodOutcome->reward.value = -5;
    option2.goodOutcome->text = "Oh no! You lost!";
    dialog.root.options.push_back( std::move( option2 ) );

    DialogOption option3;
    option3.description = "Option 3. Run away";
    option3.goodOutcome = std::make_unique<DialogNode>();
    option3.goodOutcome->text = "You ran away and got no reward";
    dialog.root.options.push_back( std::move( option3 ) );

    encounterWindow.setup( dialog.root );
}

GameModeName ModeStrategicView::handleEvents()
{
    if ( hasEventRunning() ) {
        return name;
    }

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
            else if ( encounterWindow.getRect().contains( mouseClick ) ) {
                encounterWindow.handleEvent( mouseClick, input.getModes() );
            }
        }
        else if ( input.consume( InputHandler::KEY_PRESSED ) ) {
            const char key = input.consumeKey( true );
            if ( key == 'e' ) {
                _eventTimer = GATHER_TIMER;
                _eventSubtimer = 0.0f;
                _eventType = MapEventType::GATHERING;
            }
            else if ( key == 'q' ) {
                _eventTimer = SLEEP_TIMER;
                _eventType = MapEventType::SLEEP;
            }
            else if ( key == SDL_SCANCODE_F1 ) {
                _hotkeysShown = !_hotkeysShown;
            }
        }
        return name;
    }
    return GameModeName::QUIT_GAME;
}

void ModeStrategicView::update( float deltaTime )
{
    temporaryUI.update( deltaTime );

    if ( hasEventRunning() ) {
        executeEvent( deltaTime );
        return;
    }

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
                    passTime( 1800 );
                    break;
                case WaveTile::SAND:
                    passTime( 1200 );
                    break;
                default:
                    passTime( 600 );
                    break;
                }
            }

            const int timeInHours = _state.gameTime / 3600;
            const int hours = ( timeInHours ) % 24;
            const int days = timeInHours / 24;

            std::cout << std::format( "Day {} {}: Moved to next tile\n", days, hours );

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
    _lResources.setText( std::format( "Food {}, Gold {}, Resources {}", _state.food, _state.gold, _state.resources ) );

    _mapView.render();
    _lResources.render();

    if ( hasEventRunning() ) {
        if ( _eventType == MapEventType::SLEEP ) {
            RenderEngine::Get().DrawText( "Zz..", RenderEngine::GetScreenSize().modDiv( 2 ) );
        }
        else if ( _eventType == MapEventType::GATHERING ) {
            RenderEngine::Get().DrawText( "E", RenderEngine::GetScreenSize().modDiv( 2 ) );
        }
    }

    if ( _hotkeysShown ) {
        RenderEngine::Get().DrawText( "F1 to hide hotkeys", { 10, 200 }, StandardFont::SMALL );
        RenderEngine::Get().DrawText( "Q to sleep", { 10, 230 }, StandardFont::SMALL );
        RenderEngine::Get().DrawText( "E to interact", { 10, 250 }, StandardFont::SMALL );
    }

    temporaryUI.render();

    _bOpenMenu.render();
    _bEndTurn.render();

    _menuPopup.render();
    encounterWindow.render();
}

bool ModeStrategicView::hasEventRunning() const
{
    return _eventTimer > 0;
}

RandomEncounter::RandomEncounter( const DialogTree & dialog )
    : Window( RenderEngine::GetAnchorRect( AnchorPoint::CENTER, 800, 600 ), "Random Encounter" )
    , dialog( dialog )
{
    setup( dialog.root );
}

void RandomEncounter::setup( const DialogNode & node )
{
    _components.clear();
    currentNode = &node;
    addComponent( std::make_shared<CenteringLabel>( CenteringLabel( { _rect.pos.x + 10, _rect.pos.y + 40, 780, 0 }, node.text ) ) );

    static const Style buttonStyle{ StandardFont::REGULAR, StandardColor::WHITE, StandardColor::DARK_GREY, StandardColor::REALM_PRECISION, 2 };
    int yOffset = 380;
    for ( auto & option : node.options ) {
        addComponent( std::make_shared<Button>( Button( { _rect.pos.x + 75, _rect.pos.y + yOffset, 650, 50 }, option.description, buttonStyle ) ) );

        yOffset += 70;
    }
}

int RandomEncounter::handleEvent( const Point & click, int event )
{
    for ( size_t index = 0; index < _components.size(); index++ ) {
        if ( const int result = _components[index]->handleEvent( click, event ) ) {
            setup( *currentNode->options.at( index - 1 ).goodOutcome );
            return result;
        }
    }
    return UIComponent::NO_EVENT;
}
