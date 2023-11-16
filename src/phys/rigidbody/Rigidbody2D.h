#pragma once
#include "../../template.h"

namespace Tmpl8
{
    
    class Rigidbody2D
    {
    public:
        vec2 GetPosition() const;
        void SetPosition(const vec2& newPosition);

    private:
        vec2 position = vec2();
        vec2 vel;
        vec2 damp;
    };
    
}
