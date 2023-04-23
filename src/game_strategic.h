#pragma once

#include "gamemode.h"
#include "mapview.h"
#include "ui.h"
#include "wave_function.h"

class ModeStrategicView : public GameMode
{
    WaveMap _map;
    MapView _mapView;

    float _scrollTimer = 0.0f;

    Label _lResources;
    Button _bOpenMenu;
    Button _bEndTurn;

public:
    ModeStrategicView();
    virtual GameModeName handleEvents() override;
    virtual void update( float deltaTime ) override;
    virtual void render() override;
};
