#include "particle.h"

namespace
{
    const int SUBDIVISION = 1000;
}

Particle::Particle( Point pos, Point target, int size, int speed, float lifetime )
    : position( pos.modMul( SUBDIVISION ) )
    , target( target.modMul( SUBDIVISION ) )
    , size( size )
    , speed( speed )
    , lifetime( lifetime )
{}

Point Particle::getDrawPosition() const
{
    return position.div( SUBDIVISION );
}

Rect Particle::getDrawRect() const
{
    return { getDrawPosition(), { size, size } };
}

void Particle::update( float delta )
{
    lifetime -= delta;

    Point diff = target - position;
    int max = std::max( std::abs( diff.x ), std::abs( diff.y ) );
    if ( max != 0 && max > speed ) {
        // normalize
        const float vectorX = (float)diff.x / max;
        const float vectorY = (float)diff.y / max;
        const float speedFactor = sqrtf( vectorX * vectorX + vectorY * vectorY );
        position.x += vectorX * speed / speedFactor;
        position.y += vectorY * speed / speedFactor;
    }
}
