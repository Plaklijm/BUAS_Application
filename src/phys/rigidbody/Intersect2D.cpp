#include "Intersect2D.h"

#include <windows.h>

#include "../../template.h"
#include "../primitives/AABB.h"
#include "../primitives/Circle.h"

namespace Tmpl8
{
    // CIRCLE COLLISION
    bool Intersect2D::CircleVsCircle(const Circle& c1, const Circle& c2)
    {
        auto vecBetweenCenters = vec2(c1.GetCenter() - c2.GetCenter());
        const float radiiSum = c1.GetRadius() + c2.GetRadius();
        return vecBetweenCenters.length() <= radiiSum * radiiSum;
    }

    bool Intersect2D::CircleVsAABB(const Circle& c, const AABB& b)
    {
        const vec2 min = b.GetMin();
        const vec2 max = b.GetMax();

        auto closestPointToCircle = vec2(c.GetCenter());

        if (closestPointToCircle.x < min.x) {
            closestPointToCircle.x = min.x;
        } else if (closestPointToCircle.x > min.x) {
            closestPointToCircle.x = max.x;
        }

        if (closestPointToCircle.y < min.y) {
            closestPointToCircle.y = min.y;
        } else if (closestPointToCircle.y > min.y) {
            closestPointToCircle.y = max.y;
        }

        auto compare = vec2(c.GetCenter() - closestPointToCircle);
        return compare.length() <= c.GetRadius() * c.GetRadius();
    }

    // AABB COLLISION
    bool Intersect2D::AABBVsCircle(const AABB& b, const Circle& c)
    {
        return CircleVsAABB(c, b);
    }


    bool Intersect2D::AABBVsAABB(const AABB& b1, const AABB& b2)
    {
        vec2 axesToTest[] = { vec2(0,1), vec2(1,0) };
        for (const auto axis : axesToTest)
        {
            if (!OverlapOnAxis(b1, b2, axis))
            {
                return false;
            }
        }

        return true;
    }

    bool Intersect2D::OverlapOnAxis(const AABB& b1, const AABB& b2, vec2 axis)
    {
        const vec2 interval1 = GetInterval(b1, axis);
        const vec2 interval2 = GetInterval(b2, axis);
        return interval2.x <= interval1.y && interval1.x <= interval2.y;
    }

    vec2 Intersect2D::GetInterval(const AABB& b, vec2 axis)
    {
        auto result = vec2(0,0);

        const auto min = b.GetMin();
        const auto max = b.GetMax();

        vec2 vertices[] = {
            vec2(min.x, min.y),
            vec2(min.x, max.y),
            vec2(max.x, min.y),
            vec2(max.x, max.y)
        };

        result.x = axis.dot(vertices[0]);
        result.y = result.x;

        for (auto vertex : vertices)
        {
            const float projection = axis.dot(vertex);
            if (projection < result.x)
            {
                result.x = projection;
            }
            if (projection > result.y)
            {
                result.y = projection;
            }
        }
        
        return result;
    }
}

