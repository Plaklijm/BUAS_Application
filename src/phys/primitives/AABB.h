#pragma once

#include "../../template.h"
#include "../rigidbody/Rigidbody2D.h"

// Axis Aligned Bounding Box
namespace Tmpl8
{
    
    class AABB
    {
    public:
        AABB(vec2 min, vec2 max);

        vec2 GetMin() const;
        vec2 GetMax() const;

        void SetRigidBody(Rigidbody2D rb);
        void SetSize(vec2 size);

    private:
        vec2 size = vec2();
        vec2 halfSize = vec2();

        Rigidbody2D rb;
    };
    
}
