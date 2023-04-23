#pragma once
#include <iostream>
#include <vector>

#include "base_game.h"
#include "input.h"
#include "mapview.h"
#include "wave_function.h"

class GameMode;

class Game : public BaseGame
{
    bool _isRunning = false;

    float _scrollTimer = 0.0f;

    // Add any additional game state variables or components here
    WaveMap _map;
    MapView _mapView;
    GameMode * _currentMode = nullptr;

public:
    Game()
        : _map( 32 )
    {}
    ~Game() {
        cleanup();
    }

    bool init();
    void handleEvents();
    void update( float deltaTime );
    void render() override;
    void run();
    void cleanup();
};
