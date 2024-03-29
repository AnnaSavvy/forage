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

void ParticleSystem::update( float deltaTime )
{
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
    cleanupTimer = 0;
}
