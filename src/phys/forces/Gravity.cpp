#include "Gravity.h"
#include "../rigidbody/Rigidbody2D.h"

namespace Tmpl8
{
    Gravity::Gravity(vec2 force)
    {
        this->gravity = force;
    }

    void Gravity::UpdateForce(Rigidbody2D rb, float dt)
    {
        rb.AddForce(this->gravity * rb.GetMass());
    }
}
