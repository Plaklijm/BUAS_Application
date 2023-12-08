#pragma once
#include <map>
#include <vector>

#include "../template.h"
using namespace Tmpl8;


class World
{
public:
    World() = default;

    // World Data 
    std::vector<struct Body*>                       bodies;
    std::map<struct ArbiterKey, struct Arbiter>     arbiters;
    
    vec2                                            gravity;
    int                                             iterations;

    // World physics functions
    void BroadPhase();
    void ApplyForces(float dt);
    void UpdatePositions(float dt);
};

