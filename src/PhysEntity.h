﻿#pragma once
#include "template.h"
#include "World/World.h"

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
    World world;
    PhysEntity();
    PhysEntity(vec2 center, vec2 halfSize);
    virtual ~PhysEntity() = default;
protected:
    vec2 position, oldPosition;
    vec2 acceleration;
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

protected:
    virtual void UpdatePhysics(float dt);

    bool HasGround(float& groundY);
};
