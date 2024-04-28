#include "game_battle.h"
#include "input.h"
#include "renderer.h"
#include "rpg_generation.h"
#include "timer.h"

#include <format>

namespace
{
    const int BATTLE_TILE = 96;
    const int PADDING = 5;
    const int ANIM_DELAY = 100;
}

ModeBattle::ModeBattle( GameState & state )
    : _title( { 0, 0, RenderEngine::GetScreenSize().x, 50 }, "Battle" )
    , _bExit( RenderEngine::GetAnchorRect( AnchorPoint::BOTTOM_RIGHT, 270, 80 ), "Return", {} )
    , _arena( *this, state.battle.playerForce, state.battle.otherForce )
    , temporaryUI( {} )
{
    name = GameModeName::BATTLE;
}

GameModeName ModeBattle::handleEvents()
{
    InputHandler & input = InputHandler::Get();

    if ( input.handleEvent() ) {
        if ( input.isSet( InputHandler::MOUSE_CLICKED ) ) {
            const Point & mouseClick = input.getClickPosition();
            if ( _bExit.getRect().contains( mouseClick ) ) {
                return GameModeName::CANCEL;
            }
            else if ( !_arena.executeTurn( targetIndex ) && _arena.checkIfCombatEnded() ) {
                processCombatResult();
                return GameModeName::CANCEL;
            }
        }
        else if ( input.isSet( InputHandler::MOUSE_MOVED ) ) {
            for ( int i = 0; i < 8; ++i ) {
                if ( getUnitArea( i ).contains( input.getClickPosition() ) ) {
                    targetIndex = i;
                    break;
                }
            }
        }
        else if ( input.consume( InputHandler::KEY_PRESSED ) ) {
            const char key = input.consumeKey( true );
            if ( key == '1' ) {
            }
        }
        return name;
    }
    return GameModeName::QUIT_GAME;
}

void ModeBattle::update( float deltaTime )
{
    _animTimer += deltaTime;
    temporaryUI.update( deltaTime );

    for ( auto & unit : _arena.getAttackers().modifyCharacters( RPG::Force::ALL ) ) {
        unit.get().update( deltaTime );
    }
    for ( auto & unit : _arena.getDefenders().modifyCharacters( RPG::Force::ALL ) ) {
        unit.get().update( deltaTime );
    }
}

void ModeBattle::render()
{
    const RPG::Force & left = _arena.getAttackers();
    const RPG::Force & right = _arena.getDefenders();
    const Point & screenSize = RenderEngine::GetScreenSize();

    const int tileSize = BATTLE_TILE + PADDING;

    Rect target = { ( screenSize.x - BATTLE_TILE ) / 2, ( screenSize.y - BATTLE_TILE ) / 2, tileSize, tileSize };
    target.pos.x -= tileSize * 6;
    target.pos.y -= tileSize * 3;
    for ( int i = 0; i < 6; i++ ) {
        for ( int j = 0; j < 11; j++ ) {
            target.pos.x += tileSize;
            RenderEngine::Draw( j % 2 ? "assets/t_plains.png" : "assets/t_forest.png", target );
        }
        target.pos.x -= tileSize * 11;
        target.pos.y += tileSize;
    }

    renderForce( left, false );
    renderForce( right, true );

    _title.render();
    _bExit.render();

    temporaryUI.render();
}

Rect ModeBattle::getUnitArea( int targetIndex ) const
{
    const int offset = BATTLE_TILE + PADDING;
    Rect unitArea{ RenderEngine::GetScreenSize().modSub( BATTLE_TILE, BATTLE_TILE ).modDiv( 2 ).modSub( offset * 4, 0 ), { BATTLE_TILE, BATTLE_TILE } };
    unitArea.modAdd( offset * targetIndex, 0 );
    if ( targetIndex >= 4 ) {
        unitArea.modAdd( offset, 0 );
    }
    return unitArea;
}

void ModeBattle::damageEvent( int targetIndex, int amount )
{
    RPG::BattleUnit * unit = _arena.getUnitByIndex( targetIndex );
    if ( !unit ) {
        return;
    }

    Rect unitArea = getUnitArea( targetIndex );
    StandardColor color = amount < 0 ? StandardColor::HIGHLIGHT_RED : StandardColor::REALM_NATURE;
    temporaryUI.addElement(
        std::make_shared<FlyingText>( unitArea.pos.add( 80, -8 ), std::format( "{}{}", ( amount > 0 ) ? "+" : "", amount ), 3, StandardFont::REGULAR, color ) );

    unit->effect = 1;

    const int delay = 1000;
    const int interval = delay / 20;
    SimpleTimer eventTimer{ delay };

    while ( eventTimer.isRunning() ) {
        eventTimer.run( interval );
        update( interval / 1000.0f );
        render();
        RenderEngine::Get().Present();
    }

    unit->effect = 0;
}

void ModeBattle::renderForce( const RPG::Force & target, bool mirror )
{
    const Point & screenSize = RenderEngine::GetScreenSize();
    const std::vector<RPG::Force::Position> positions = { RPG::Force::FRONT, RPG::Force::SIDE, RPG::Force::CENTER, RPG::Force::BACK };

    Rect drawArea = { { ( screenSize.x - BATTLE_TILE ) / 2, ( screenSize.y - BATTLE_TILE ) / 2 }, { BATTLE_TILE, BATTLE_TILE } };

    for ( auto & position : positions ) {
        const int offset = ( mirror ) ? BATTLE_TILE + PADDING : -BATTLE_TILE - PADDING;
        drawArea.pos.x += offset;

        auto units = target.getCharacters( position );
        if ( !units.empty() ) {
            const RPG::BattleUnit & unit = units.front().get();

            switch ( unit.effect ) {
            case 1:
                RenderEngine::DrawTinted( unit.getSprite(), drawArea, StandardColor::REALM_CHAOS, mirror );
                break;
            default:
                RenderEngine::Draw( unit.getSprite(), drawArea, mirror );
                break;
            }
            if ( _arena.getCurrentUnit() && _arena.getCurrentUnit()->getId() == unit.getId() ) {
                StandardColor markColor = unit.rightSide ? StandardColor::HIGHLIGHT_RED : StandardColor::REALM_PRECISION;
                RenderEngine::DrawPieSlice( { drawArea.pos.add( BATTLE_TILE / 2, 0 ), { 30, 30 } }, 255, 285, markColor );
            }

            Point textPosition = drawArea.pos;
            if ( mirror ) {
                textPosition.x += BATTLE_TILE - 22;
            }
            RenderEngine::DrawText( std::to_string( unit.getCurrentHealth() ), textPosition );

            const RPG::BattleUnit * target = _arena.getUnitByIndex( targetIndex );
            if ( target && target->getId() == unit.getId() ) {
                RenderEngine::Draw( targetIndex < 4 ? "assets/mask_target_1.png" : "assets/mask_target_0.png", drawArea );
            }
        }
    }
}

void ModeBattle::processCombatResult() 
{
    // update game state

    displayCombatResult();
}

void ModeBattle::displayCombatResult()
{
    Rect overlayArea = RenderEngine::GetAnchorRect( AnchorPoint::CENTER, 640, 480 );
    std::shared_ptr<UIContainer> overlay = std::make_shared<UIContainer>( overlayArea.pos );

    const int delay = 2000;
    const int updates = 20;
    const int interval = delay / updates;
    SimpleTimer eventTimer{ delay };

    for ( int i = 0; i < updates; i++ ) {
        eventTimer.run( interval );
        RenderEngine::Get().applyTint( StandardColor::BLACK, i * 0.06 );
        update( interval / 1000.0f );
        render();
        RenderEngine::Get().Present();
    }
    RenderEngine::Get().applyTint( StandardColor::WHITE );
}
