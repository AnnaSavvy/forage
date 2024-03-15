#pragma once

#include "game_state.h"
#include "gamemode.h"
#include "rpg_arena.h"
#include "ui.h"

class ModeBattle : public GameMode
{
    CenteringLabel _title;
    Button _bExit;
    RPG::Arena _arena;

    float _animTimer = 0;

    void renderForce( const RPG::Force & target, bool mirror );

public:
    ModeBattle( GameState & state );
    virtual GameModeName handleEvents() override;
    virtual void update( float deltaTime ) override;
    virtual void render() override;
};
