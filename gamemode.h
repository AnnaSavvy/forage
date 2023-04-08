#pragma once

#include "mapview.h"
#include "wave_function.h"

enum class GameModeName : int
{
    CANCEL = 0,
    QUIT_GAME,
    MAIN_MENU,
    NEW_GAME,
    LOAD_GAME,
    HIGHSCORES,
    CREDITS,
    GAME_ONGOING
};

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
    WaveMap _map;
    MapView _mapView;

public:
    ModeMainMenu();
    virtual GameModeName handleEvents() override;
    virtual void update( float deltaTime ) override;
    virtual void render() override;
};
