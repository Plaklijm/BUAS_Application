#pragma once
#include <memory>

#include "../../template.h"

// Axis Aligned Bounding Box
namespace Tmpl8
{
    class Rigidbody2D;
    
    class AABB
    {
    public:
        AABB(vec2 min, vec2 max);
        vec2 GetMin() const;
        vec2 GetMax() const;

    private:
        vec2 size = vec2();
        vec2 halfSize = vec2();

        std::unique_ptr<Rigidbody2D> rb = nullptr;
    };
    
}
