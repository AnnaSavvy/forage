#pragma once
#include <iostream>
#include <vector>

#include "base_game.h"
#include "mapview.h"
#include "wave_function.h"

class Game : public BaseGame
{
    bool _isRunning = false;

    float _scrollTimer = 0.0f;
    bool _scrollingLeft = false;
    bool _scrollingRight = false;
    bool _scrollingUp = false;
    bool _scrollingDown = false;

    // Add any additional game state variables or components here
    WaveMap _map;
    MapView _mapView;

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
