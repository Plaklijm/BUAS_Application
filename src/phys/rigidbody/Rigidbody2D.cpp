#include "Rigidbody2D.h"

namespace Tmpl8
{
    vec2 Rigidbody2D::GetPosition() const
    {
        return this->position;
    }

    void Rigidbody2D::SetPosition(const vec2& newPosition)
    {
        this->position = newPosition;
    }
}
