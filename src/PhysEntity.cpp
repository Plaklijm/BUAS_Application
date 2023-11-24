﻿#include "PhysEntity.h"

#include "AABB.h"

PhysEntity::PhysEntity()
{
}

PhysEntity::PhysEntity(vec2 center, vec2 halfSize)
{
    aabb = new AABB(center, halfSize);
}

void PhysEntity::UpdatePhysics(float dt)
{
    // Set old variables
    oldPosition = position;
    oldSpeed = speed;

    wasOnGround = onGround;
    wasAtCeiling = atCeiling;
    pushedLeftWall = pushesLeftWall;
    pushedRightWall = pushesRightWall;

    // Update frame independent position 
    position += speed * dt;

    if (position.y <= ScreenHeight-50) {
        position.y = ScreenHeight-50;
        onGround = true;
    } else {
        onGround = false;
    }

    aabb->SetCenter(position + aabbOffset); 
}
