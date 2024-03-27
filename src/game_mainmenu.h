#pragma once

#include "gamemode.h"
#include "mapview.h"
#include "particle_system.h"
#include "ui_base.h"
#include "wave_function.h"

class ParticleSystem;

class ModeMainMenu : public GameMode
{
    WaveMap _backgroundMap;
    MapView _mapView;
    ParticleSystem _particles;

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
