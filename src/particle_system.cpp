#include "particle_system.h"
#include "renderer.h"

namespace
{
    const float CLEANUP_DELAY = 5.0f;
}

void ParticleSystem::cleanup()
{
    if ( cleanupTimer > CLEANUP_DELAY && !items.empty() ) {
        std::vector<Particle> clean;
        for ( auto particle : items ) {
            if ( particle.lifetime > 0 ) {
                clean.push_back( std::move( particle ) );
            }
        }
        items = clean;
        cleanupTimer = 0;
    }
}

bool ParticleSystem::add( Particle item )
{
    if ( items.size() < particleLimit ) {
        items.push_back( item );
        return true;
    }
    return false;
}

void ParticleSystem::addEmitter( ParticleEmitter emitter )
{
    emitters.push_back( emitter );
}

void ParticleSystem::update( float deltaTime )
{
    for ( auto & emitter : emitters ) {
        emitter.update( deltaTime );
    }
    for ( auto & particle : items ) {
        particle.update( deltaTime );
    }

    cleanupTimer += deltaTime;
    cleanup();
}

void ParticleSystem::render()
{
    for ( auto & particle : items ) {
        if ( particle.lifetime > 0 ) {
            RenderEngine::DrawRect( particle.getDrawRect(), StandardColor::HIGHLIGHT_RED );
        }
    }
}

void ParticleSystem::reset()
{
    items.clear();
    emitters.clear();
    cleanupTimer = 0;
}

ParticleEmitter::ParticleEmitter( ParticleSystem & system, Point pos, float frequency )
    : system( system )
    , position( pos )
    , frequency( frequency )
{}

void ParticleEmitter::update( float deltaTime ) {
    timer += deltaTime;
    while ( timer > frequency ) {
        system.add( { position, { 1275, angle * 2 }, 2, 1000, 10 } );

        angle = ( angle + 10 ) % 360;
        timer -= frequency;
    }
}

void ParticleEmitter::reset( float newFrequency )
{
    done = false;
    frequency = newFrequency;
    timer = 0;
}
