#include "game_strategic.h"
#include "build_optimizer.h"
#include "dialog.h"
#include "input.h"
#include "renderer.h"
#include "rng.h"
#include "static.h"

#include <SDL_scancode.h>
#include <format>
#include <iostream>

namespace
{
    const float GATHER_TIMER = 6;
    const float SLEEP_TIMER = 4;

    class RandomEncounter : public Window
    {
        std::function<void(const Reward &)> resultCallback;
        DialogTree dialog;
        const DialogNode * currentNode = nullptr;

    public:
        RandomEncounter( DialogTree dialog, std::function<void( const Reward & )> callback );

        void setup( const DialogNode & node );
        int handleEvent( const Point & click, int event ) override;
    };
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
            _state.player.food++;
            temporaryUI.addElement( std::make_shared<FlyingText>( RenderEngine::GetScreenSize().modDiv( 2 ).add( 40, 0 ), "+1", 3 ) );
        }
    }

    if ( _eventTimer <= 0 ) {
        _eventType = MapEventType::NO_EVENT;
    }
}

void ModeStrategicView::processReward( const Reward & reward )
{
    if ( reward.type == Reward::Type::BATTLE ) {
        _state.battle.difficulty = reward.value;
        _state.battle.variety = reward.metadata;
        runBattle = true;
    }
    else {
        _state.recieveReward( reward );
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
{
    name = GameModeName::NEW_GAME;

    _map.updateMap();
    _mapView.setMap( _map );
    _mapView.setPlayer( "assets/char.png" );

    _menuPopup.setHidden( true );

    Style buttonStyle{ StandardFont::REGULAR_BOLD, StandardColor::HIGHLIGHT_RED, StandardColor::BLACK, StandardColor::DARK_GREY, 5 };
    _bOpenMenu.setStyle( buttonStyle );
    _bEndTurn.setStyle( buttonStyle );
}

GameModeName ModeStrategicView::handleEvents()
{
    if ( runBattle ) {
        runBattle = false;
        return GameModeName::BATTLE;
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
            else if ( activeWindow && activeWindow->getRect().contains( mouseClick ) ) {
                int status = activeWindow->handleEvent( mouseClick, input.getModes() );
                if ( status == UIComponent::CLOSE_WINDOW ) {
                    activeWindow = nullptr;
                    _eventType = MapEventType::NO_EVENT;
                }
            }
        }
        else if ( !hasEventRunning() && input.consume( InputHandler::KEY_PRESSED ) ) {
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

    if ( _eventTimer > 0 ) {
        executeEvent( deltaTime );
        return;
    }

    if ( hasEventRunning() ) {
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
                _eventType = MapEventType::ENCOUNTER;
                activeWindow = std::make_unique<RandomEncounter>( GetDialogTree(), std::bind( &ModeStrategicView::processReward, this, std::placeholders::_1 ) );
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
    _lResources.setText( std::format( "Food {}, Gold {}, Resources {}", _state.player.food, _state.player.gold, _state.player.resources ) );

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

    if ( activeWindow ) {
        activeWindow->render();
    }
}

bool ModeStrategicView::hasEventRunning() const
{
    return _eventType != MapEventType::NO_EVENT;
}

RandomEncounter::RandomEncounter( DialogTree dialog, std::function<void( const Reward & )> callback )
    : Window( RenderEngine::GetAnchorRect( AnchorPoint::CENTER, 800, 600 ), "Random Encounter" )
    , resultCallback( callback )
    , dialog( std::move( dialog ) )
{
    setup( this->dialog.root );
}

void RandomEncounter::setup( const DialogNode & node )
{
    _components.clear();
    currentNode = &node;

    resultCallback( currentNode->reward );

    addComponent( std::make_shared<CenteringLabel>( CenteringLabel( { _rect.pos.x + 10, _rect.pos.y + 100, 780, 0 }, node.text ) ) );

    static const Style buttonStyle{ StandardFont::REGULAR, StandardColor::WHITE, StandardColor::DARK_GREY, StandardColor::REALM_PRECISION, 2 };
    int yOffset = 380;
    for ( auto & option : node.options ) {
        addComponent( std::make_shared<Button>( Button( { _rect.pos.x + 75, _rect.pos.y + yOffset, 650, 50 }, option.description, buttonStyle ) ) );

        yOffset += 70;
    }

    if ( node.options.empty() ) {
        addComponent( std::make_shared<Button>( Button( { _rect.pos.x + 75, _rect.pos.y + 500, 650, 50 }, "Close dialog", buttonStyle ) ) );
    }

    if ( currentNode->reward.value != 0 ) {
        std::string rewardText = std::format( "Your reward: {} gold!", currentNode->reward.value );
        addComponent( std::make_shared<CenteringLabel>( CenteringLabel( { _rect.pos.x + 50, _rect.pos.y + 150, 700, 0 }, rewardText ) ) );
    }
}

int RandomEncounter::handleEvent( const Point & click, int event )
{
    for ( size_t index = 0; index < _components.size(); index++ ) {
        if ( const int result = _components[index]->handleEvent( click, event ) ) {
            if ( currentNode->options.empty() ) {
                return UIComponent::CLOSE_WINDOW;
            }

            const DialogOption & option = currentNode->options.at( index - 1 );

            bool failedCheck = false;
            if ( option.difficulty ) {
                failedCheck = RandomGenerator::Get().next( 1, 20 ) < option.difficulty;
            }

            if ( failedCheck && option.badOutcome ) {
                setup( *option.badOutcome );
            }
            else if ( option.goodOutcome ) {
                setup( *option.goodOutcome );
            }
            return result;
        }
    }
    return UIComponent::NO_EVENT;
}
