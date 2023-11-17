#pragma once
#include "ForceGenerator.h"
#include "../../template.h"

namespace Tmpl8
{
    class Gravity : ForceGenerator
    {
    public:
        Gravity(vec2 force);
        
        void UpdateForce(Rigidbody2D rb, float dt) override;
        
    private:
        vec2 gravity;
    };
}
    
