#pragma once
#include "particle.h"

struct ParticleEmitter
{};

class ParticleSystem
{
    int particleLimit = 37;
    std::vector<Particle> items;

public:
    void add( Particle item );
    void update( float deltaTime );
    void render();
};
