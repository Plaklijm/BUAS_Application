#pragma once
#include "ForceGenerator.h"
#include "../rigidbody/Rigidbody2D.h"

namespace Tmpl8
{

    class ForceRegistration
    {
    public:
        ForceRegistration(const ForceGenerator& fg, const Rigidbody2D& rb);
        
        ForceGenerator fg;
        Rigidbody2D rb;
    };
}

