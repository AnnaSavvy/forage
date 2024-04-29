#pragma once

#include "game_state.h"
#include "gamemode.h"
#include "rpg_arena.h"
#include "ui_base.h"

class ModeBattle : public GameMode
{
    UIContainer temporaryUI;
    CenteringLabel _title;
    Button _bExit;
    UIContainer actionBar;
    RPG::Arena _arena;

    float _animTimer = 0;
    int targetIndex = -1;

    void renderForce( const RPG::Force & target, bool mirror );
    void processCombatResult();
    void displayCombatResult();

public:
    ModeBattle( GameState & state );
    virtual GameModeName handleEvents() override;
    virtual void update( float deltaTime ) override;
    virtual void render() override;

    Rect getUnitArea( int targetIndex ) const;
    void damageEvent( int targetIndex, int amount );
};
