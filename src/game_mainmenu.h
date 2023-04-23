#pragma once

#include "gamemode.h"
#include "mapview.h"
#include "ui.h"
#include "wave_function.h"

class GameMode
{
    GameModeName name = GameModeName::CANCEL;

public:
    virtual GameModeName handleEvents() = 0;
    virtual void update( float deltaTime ) = 0;
    virtual void render() = 0;
};

class ModeMainMenu : public GameMode
{
    WaveMap _backgroundMap;
    MapView _mapView;

    Label _title;
    Button _bNewGame;
    Button _bLoadGame;
    Button _bOptions;
    Button _bQuitGame;

public:
    ModeMainMenu();
    virtual GameModeName handleEvents() override;
    virtual void update( float deltaTime ) override;
    virtual void render() override;
};
