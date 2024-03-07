#pragma once

#include "character.h"
#include "game_state.h"
#include "gamemode.h"
#include "ui.h"

class ModeBuildCalculator : public GameMode
{
    GameState & _state;
    RPG::Character _character;

    Label _title;
    Button _bExit;

    Label _charName;
    Button _bGenerateName;

    UIContainer skills;

public:
    ModeBuildCalculator( GameState & state );
    virtual GameModeName handleEvents() override;
    virtual void update( float deltaTime ) override;
    virtual void render() override;
};
