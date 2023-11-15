#pragma once
#include "../template.h"

using namespace Tmpl8;

struct body
{
    body();

    void applyForce(const vec2& _force);
    
    vec2 pos;
    vec2 vel;

    vec2 width;
    float friction;
    float mass, invMass;
    float I, invI;

    vec2 force;
};
