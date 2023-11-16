#pragma once
#include "../../template.h"

namespace Tmpl8
{
    class Circle;
    class AABB;
    
    class Intersect2D
    {
    public:
        static bool CircleVsCircle(const Circle& c1, const Circle& c2);
        static bool CircleVsAABB(const Circle& c, const AABB& b);
        static bool AABBVsCircle(const AABB& b, const Circle& c);
        static bool AABBVsAABB(const AABB& b1, const AABB& b2);

    private:
        static bool OverlapOnAxis(const AABB& b1, const AABB& b2, vec2 axis);
        static vec2 GetInterval(const AABB& b, vec2 axis);
    };
}
