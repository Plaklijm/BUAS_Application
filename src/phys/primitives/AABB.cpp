﻿#include "AABB.h"

#include "../rigidbody/Rigidbody2D.h"

namespace Tmpl8
{
    AABB::AABB(vec2 min, vec2 max)
    {
        this->size = vec2(max - min);
        this->halfSize = vec2(size * .5f);
    }

    vec2 AABB::GetMin() const
    {
        return vec2(this->rb.GetPosition() - this->halfSize);
    }

    vec2 AABB::GetMax() const
    {
        return vec2(this->rb.GetPosition() + this->halfSize);
    }

    void AABB::SetRigidBody(Rigidbody2D rb)
    {
        this->rb = rb;
    }

    void AABB::SetSize(vec2 size)
    {
        this->size = size;
        this->halfSize = size * .5f;
    }
}
