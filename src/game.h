#pragma once
#include <iostream>
#include <vector>

#include "base_game.h"
#include "input.h"
#include "mapview.h"
#include "wave_function.h"

#include <stack>

class GameMode;

class Game : public BaseGame
{
    bool _isRunning = false;

    // Add any additional game state variables or components here
    WaveMap _map;
    std::stack<std::shared_ptr<GameMode> > _modeStack;

    double _windowScaling = 1.0;
    Point _logicalSize;

public:
    Game( Point desiredSize );
    virtual ~Game();

    bool init();
    void handleEvents();
    void update( float deltaTime );
    void render() override;
    void run();
    void cleanup();
};
