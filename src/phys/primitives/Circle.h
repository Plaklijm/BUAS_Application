#pragma once
#include <memory>

#include "../../template.h"
#include "../rigidbody/Rigidbody2D.h"

namespace Tmpl8
{
    class Rigidbody2D;
    
    class Circle
    {
    public:
        Circle(float radius);

        float GetRadius() const;
        vec2 GetCenter() const;

        void SetRadius(float r);
        void SetRigidBody(Rigidbody2D rb);
    
    private:
        float radius;
        Rigidbody2D rb;
    };
    
}
