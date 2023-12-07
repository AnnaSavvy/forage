#pragma once

#include "character.h"
#include "gamemode.h"
#include "ui.h"

class ModeBuildCalculator : public GameMode
{
    RPG::Character _character;

    Label _title;
    Button _bExit;

    Label _charName;
    Button _bGenerateName;

    std::vector<ProgressBar> skills;
    std::vector<Button> increase;

public:
    ModeBuildCalculator();
    virtual GameModeName handleEvents() override;
    virtual void update( float deltaTime ) override;
    virtual void render() override;
};
