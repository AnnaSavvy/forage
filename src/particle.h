#pragma once
#include "point.h"

struct Particle
{
    Point position;
    Point target;

    int size = 1;
    float lifetime = 0;
    int speed = 0;
    int type = 0;

    Particle( Point pos, Point target, int size, int speed, float lifetime );

    Point getDrawPosition() const;
    Rect getDrawRect() const;
    void update( float delta );
};
