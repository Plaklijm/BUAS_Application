#include "Collision.h"

#include <array>

#include "AABB.h"
// https://www.youtube.com/watch?v=8JJ-4JgR7Dg

Collision::Collision()
{
}

void Collision::Update()
{
}

bool Collision::PointVsAABB(const vec2& point, const AABB& rect)
{
    return (point.x >= rect.pos.x && point.y >= rect.pos.y &&
            point.x < rect.pos.x + rect.size.x && point.y < rect.pos.y + rect.size.y);
}

bool Collision::AABBVsAABB(const AABB& rect1, const AABB& rect2)
{
    return (rect1.pos.x < rect2.pos.x + rect2.size.x && rect1.pos.x + rect1.size.x > rect2.pos.x &&
            rect1.pos.y < rect2.pos.y + rect2.size.y && rect1.pos.y + rect1.size.y > rect2.pos.y );
}

bool Collision::RayVsAABB(const vec2& rayOrigin, const vec2& rayDirection, const AABB& rect,
    vec2& contactPoint, vec2& contactNormal, float& tHitNear)
{
    vec2 near = (rect.pos - rayOrigin) / rayDirection;
    vec2 far = (rect.pos + rect.size - rayOrigin) / rayDirection;

    if (std::_Is_nan(far.y) || std::_Is_nan(far.x)) return false;
    if (std::_Is_nan(near.y) || std::_Is_nan(near.x)) return false;
            
    // Sort distances
    if (near.x > far.x) std::swap(near.x, far.x);
    if (near.y > far.y) std::swap(near.y, far.y);

    if (near.x > far.y || near.y > far.x) return false;
    
    tHitNear = std::max(near.x, near.y);
    float t_hit_far = std::min(far.x, far.y);

    // Reject if ray direction is pointing away from object
    if (t_hit_far < 0) return false;
    
    contactPoint = (rayOrigin + tHitNear) * rayDirection;

    if (near.x > near.y)
        if (rayDirection.x < 0)
            contactNormal = vec2::Right();
        else
            contactNormal = vec2::Left();
    else if (near.x < near.y)
        if (rayDirection.y < 0)
            contactNormal = vec2::Up();
        else
            contactNormal = vec2::Down();

    return true;
}

bool Collision::DynamicAABBVsAABB(const AABB& in, const AABB& target,
    vec2& contactPoint, vec2& contactNormal, float& contactTime, float dt)
{
    if (in.vel.x == 0.f && in.vel.y == 0.f) return false;

    AABB expandedTarget = {target.pos - in.size / 2, target.size + in.size};

    if (RayVsAABB(in.pos + in.size / 2, in.vel * dt, expandedTarget, contactPoint, contactNormal, contactTime))
    {
        if (contactTime <= 1.f)
            return true;
    }

    return false;
}

