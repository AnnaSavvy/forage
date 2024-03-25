#pragma once
#include "point.h"

struct Particle
{
    Point position;
    Point target;

    int size;
    float lifetime = 0;
    int speed = 0;
    int type = 0;
};
