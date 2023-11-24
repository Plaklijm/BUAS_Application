#pragma once
#include <windows.h>

#include "template.h"

using namespace Tmpl8;

/*enum currentStatusFlag
{
    pushesRightWall = 1,
    pushesLeftWall = 2,
    onGround = 4,
    atCeiling = 8
};

DEFINE_ENUM_FLAG_OPERATORS(currentStatusFlag);

enum oldStatusFlag
{
    pushedRightWall = 1,
    pushedLeftWall = 2,
    wasOnGround = 4,
    wasAtCeiling = 8
};

DEFINE_ENUM_FLAG_OPERATORS(oldStatusFlag);*/

struct AABB;

class PhysEntity
{
public:
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
    bool pushesRightWall{false};
    bool pushedLeftWall{};
    bool pushesLeftWall{false};
    bool wasOnGround{};
    bool onGround{false};
    bool wasAtCeiling{};
    bool atCeiling{};

public:
    virtual void UpdatePhysics(float dt);
};
