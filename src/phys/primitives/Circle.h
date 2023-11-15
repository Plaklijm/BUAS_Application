#pragma once
#include <memory>

#include "../../template.h"

namespace Tmpl8
{
    class Rigidbody2D;
    
    class Circle
    {
    public:
        Circle(float radius);

        float GetRadius() const;

        vec2 GetCenter() const;
    
    private:
        float radius;
        std::unique_ptr<Rigidbody2D> rb = nullptr;
    };
    
}
