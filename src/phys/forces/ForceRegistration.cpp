#include "ForceRegistration.h"

namespace Tmpl8
{
    ForceRegistration::ForceRegistration(const ForceGenerator& fg, const Rigidbody2D& rb)
    {
        this->fg = fg;
        this->rb = rb;
    }
}
