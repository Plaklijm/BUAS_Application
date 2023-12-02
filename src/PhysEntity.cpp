#include "PhysEntity.h"

#include "AABB.h"
#include <algorithm>

PhysEntity::PhysEntity()
{
}

PhysEntity::PhysEntity(vec2 center, vec2 halfSize)
{
    aabb = new AABB(center, halfSize);
    world = World();
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

    float groundY = ScreenHeight - 50;
    if (speed.y <= 0.0f && HasGround(groundY))
    {
        position.y = groundY;// + aabb->GetHalfSize().y - aabbOffset.y;
        speed.y = 0.0f;
        onGround = true;
    }
    else
        onGround = false;

    aabb->SetCenter(position + aabbOffset); 
}

bool PhysEntity::HasGround(float& groundY)
{
    /*const auto oldCenter = oldPosition + aabbOffset;
    const auto center = position + aabbOffset;
    
    auto oldBottomLeft = oldCenter - aabb->GetHalfSize() - vec2::Up() + vec2::Right();
    auto newBottomLeft = center - aabb->GetHalfSize() - vec2::Up() + vec2::Right();
    auto newBottomRight = new vec2(newBottomLeft.x + aabb->GetHalfSize().x * 2.0f - 2.0f, newBottomLeft.y);

    const int endY = world.GetMapTileYAtPoint(newBottomLeft.y);
    const int begY = std::max(world.GetMapTileYAtPoint(oldBottomLeft.y) - 1, endY);
    const int dist = std::max(std::abs(endY - begY), 1);

    for (int tileIndexY = begY; tileIndexY >= endY; --tileIndexY)
    {
        auto bottomLeft = vec2::Lerp(newBottomLeft, oldBottomLeft, (float)std::abs(endY - tileIndexY) / dist);
        auto bottomRight = vec2(bottomLeft.x + aabb->GetHalfSize().x * 2.0f - 2.0f, bottomLeft.y);
    
        for (auto checkedTile = bottomLeft; ; checkedTile.x += tileSize)
        {
            checkedTile.x = std::min(checkedTile.x, bottomRight.x);
            
            int tileIndexX = world.GetMapTileXAtPoint(checkedTile.x);
            
            groundY = float(tileIndexY) * tileSize + tileSize / 2.0f + world.position.y;
            
            if (world.IsObstacle(tileIndexX, tileIndexY))
                return true;
                
            if (checkedTile.x >= bottomRight.x)
                break;
        }
    }*/
    
    return true;
}
