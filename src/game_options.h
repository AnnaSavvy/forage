#pragma once

#include "gamemode.h"
#include "chart.h"

class ModeOptions : public GameMode
{
    Label _title;
    Button _bExit;
    Chart::Pie _realmPhysical;
    Chart::Pie _realmMagical;

public:
    ModeOptions();
    virtual GameModeName handleEvents() override;
    virtual void update( float deltaTime ) override;
    virtual void render() override;
};
