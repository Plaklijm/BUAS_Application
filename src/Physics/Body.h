#pragma once
#include "../template.h"

using namespace Tmpl8;

// https://github.com/erincatto/box2d-lite/blob/master/docs/HowDoPhysicsEnginesWork.pdf

// Static bodies:
// invMass = 0 <- this means the forces will be multiplied by 0 and thus have no impact

struct Body
{
    Body();

    void AddForce(const vec2& f)
    {
    }

    // Body state
    vec2        position;
    vec2        velocity;

    // Box properties
    float       mass;
    float       invMass; 
    float       restitution;
    float       friction;

    // Applied forces
    vec2        force;
};
