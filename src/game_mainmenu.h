#pragma once

#include "gamemode.h"
#include "mapview.h"
#include "ui.h"
#include "wave_function.h"

class ModeMainMenu : public GameMode
{
    WaveMap _backgroundMap;
    MapView _mapView;

    CenteringLabel _title;
    Button _bNewGame;
    Button _bLoadGame;
    Button _bBattle;
    Button _bOptions;
    Button _bQuitGame;

public:
    ModeMainMenu();
    virtual GameModeName handleEvents() override;
    virtual void update( float deltaTime ) override;
    virtual void render() override;
};
