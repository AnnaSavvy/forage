#pragma once

#include "game_state.h"
#include "gamemode.h"
#include "mapview.h"
#include "ui_base.h"
#include "wave_function.h"

class ModeStrategicView : public GameMode
{
    GameState _state;
    WaveMap _map;
    MapView _mapView;

    float _scrollTimer = 0.0f;

    Label _lResources;
    Button _bOpenMenu;
    Button _bEndTurn;
    Window _menuPopup;

public:
    ModeStrategicView( GameState & state );
    virtual GameModeName handleEvents() override;
    virtual void update( float deltaTime ) override;
    virtual void render() override;
};
