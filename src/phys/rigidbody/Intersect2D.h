#pragma once

namespace Tmpl8
{
    class Circle;
    class AABB;
    
    class Intersect2D
    {
    public:
        static bool CircleVsCircle(const Circle& c1, const Circle& c2);
        static bool CircleVsAABB(const Circle& c, const AABB& b);
        static bool AABBVsAABB(const AABB& b1, const AABB& b2);
    };
}

