#pragma once
#include "template.h"

using namespace Tmpl8;

struct AABB;

class PhysEntity
{
private:
    PhysEntity();
    PhysEntity(vec2 center, vec2 halfSize);
    virtual ~PhysEntity() = default;
protected:
    vec2 position, oldPosition;
    vec2 speed, oldSpeed;
    vec2 scale;

    AABB* aabb;
    vec2 aabbOffset;

    // TODO: Replace with FLAGS
    bool pushedRightWall{};
    bool pushesRightWall{};
    bool pushedLeftWall{};
    bool pushesLeftWall{};
    bool wasOnGround{};
    bool onGround{};
    bool wasAtCeiling{};
    bool atCeiling{};

public:
    virtual void UpdatePhysics(float dt);
};
