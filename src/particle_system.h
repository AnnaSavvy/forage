#pragma once
#include "particle.h"

struct ParticleEmitter
{};

class ParticleSystem
{
    int particleLimit = 37;
    float cleanupTimer = 0.0;
    std::vector<Particle> items;

    void cleanup();

public:
    bool add( Particle item );
    void update( float deltaTime );
    void render();
    void reset();
};
