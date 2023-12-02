#pragma once
#include "template.h"

struct AABB;
using namespace Tmpl8;

class Collision
{
public:
    Collision();

    void Update();

    static bool PointVsAABB(const vec2& point, const AABB& rect);
    static bool AABBVsAABB(const AABB& rect1, const AABB& rect2);
    static bool RayVsAABB(const vec2& rayOrigin, const vec2& rayDirection, const AABB& rect,
                          vec2& contactPoint, vec2& contactNormal, float&tHitNear);
    static bool DynamicAABBVsAABB(const AABB& in, const AABB& target, vec2& contactPoint, vec2& contactNormal, float& contactTime, float dt);
};
 