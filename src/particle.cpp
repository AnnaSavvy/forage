#include "particle.h"

void Particle::update( float delta )
{
    lifetime -= delta;

    Point diff = target - position;
    int max = std::max( diff._x, diff._y );
    if ( max != 0 ) {
        // normalize
        float vectorX = (float)diff._x / max;
        float vectorY = (float)diff._y / max;
        position._x += vectorX * speed / 100;
        position._y += vectorY * speed / 100;
    }
}