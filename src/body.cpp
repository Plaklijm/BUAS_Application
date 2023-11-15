#include "include/phys/body.h"

body::body()
{
    pos = {};
    vel = {};
}

void body::applyForce(const vec2& _force)
{
    force += _force;
}
