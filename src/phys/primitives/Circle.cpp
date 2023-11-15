#include "Circle.h"

#include "../rigidbody/Rigidbody2D.h"

namespace Tmpl8
{
    Circle::Circle(float radius)
    {
        this->radius = radius;
    }

    float Circle::GetRadius() const
    {
        return this->radius;
    }

    vec2 Circle::GetCenter() const
    {
        return this->rb->GetPosition();
    }
}
