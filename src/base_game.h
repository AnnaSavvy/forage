#pragma once

class BaseGame
{
public:
    virtual bool init() = 0;
    virtual void handleEvents() = 0;
    virtual void update( float deltaTime ) = 0;
    virtual void render() = 0;
    virtual void run() = 0;
    virtual void cleanup() = 0;
};
