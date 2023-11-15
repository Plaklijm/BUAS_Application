#include "Intersect2D.h"

#include "../../template.h"
#include "../primitives/AABB.h"
#include "../primitives/Circle.h"

namespace Tmpl8
{
    bool Intersect2D::CircleVsCircle(const Circle& c1, const Circle& c2)
    {
        vec2 vecBetweenCenters = vec2(c1.GetCenter() - c2.GetCenter());
        const float radiiSum = c1.GetRadius() + c2.GetRadius();
        return vecBetweenCenters.length() <= radiiSum * radiiSum;
    }

    bool Intersect2D::CircleVsAABB(const Circle& c, const AABB& b)
    {
        const vec2 min = b.GetMin();
        const vec2 max = b.GetMax();

        vec2 closestPointToCircle = vec2(c.GetCenter());

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

        vec2 compare = vec2(c.GetCenter() - closestPointToCircle);
        return compare.length() <= c.GetRadius() * c.GetRadius();
    }

    bool Intersect2D::AABBVsAABB(const AABB& b1, const AABB& b2)
    {
    }
}

