#pragma once
#include "particle.h"

class ParticleEmitter;

class ParticleSystem
{
    int particleLimit = 100000;
    float cleanupTimer = 0.0;
    std::vector<Particle> items;
    std::vector<ParticleEmitter> emitters;

    void cleanup();

public:
    bool add( Particle item );
    void addEmitter( ParticleEmitter emitter );
    void update( float deltaTime );
    void render();
    void reset();
};

class ParticleEmitter
{
    ParticleSystem & system;
    bool done = true;
    float timer = 0;

public:
    float frequency = 0;
    int angle = 0;
    int distance = 1000;
    Point position;

    ParticleEmitter( ParticleSystem & system, Point pos, float frequency );
    void update( float deltaTime );
    void reset( float newFrequency );
};
