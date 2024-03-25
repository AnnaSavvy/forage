#include "particle_system.h"
#include "renderer.h"

void ParticleSystem::add( Particle item )
{
    items.push_back( item );
}

void ParticleSystem::update( float deltaTime )
{
    for ( auto particle : items ) {
        particle.lifetime -= deltaTime;
        if ( particle.lifetime < 0 ) {
            // kill
        }
    }
}

void ParticleSystem::render()
{
    for ( auto particle : items ) {
        if ( particle.lifetime > 0 ) {
            RenderEngine::DrawRect( { particle.position, { particle.size, particle.size } }, StandardColor::HIGHLIGHT_RED );
        }
    }
}
