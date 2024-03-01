#pragma once

#include "gamemode.h"
#include "game_state.h"
#include "rpg_arena.h"
#include "ui.h"

class ModeBattle : public GameMode
{
    Label _title;
    Button _bExit;
    RPG::Arena arena;

public:
    ModeBattle( GameState state );
    virtual GameModeName handleEvents() override;
    virtual void update( float deltaTime ) override;
    virtual void render() override;
};
