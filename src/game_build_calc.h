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

    std::vector<std::shared_ptr<UIComponent>> skills;

public:
    ModeBuildCalculator();
    virtual GameModeName handleEvents() override;
    virtual void update( float deltaTime ) override;
    virtual void render() override;
};
