#pragma once

#include "gamemode.h"
#include "chart.h"
#include "character_class.h"

class ModeOptions : public GameMode
{
    Label _title;
    Button _bExit;
    Chart::Pie _realmPhysical;
    Chart::Pie _realmMagical;
    CharacterClass current = CharacterClass::DEFAULT;
    int inputDelay = 0;

public:
    ModeOptions();
    virtual GameModeName handleEvents() override;
    virtual void update( float deltaTime ) override;
    virtual void render() override;
    void pick( CharacterClass name );
};
