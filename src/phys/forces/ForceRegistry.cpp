#include "ForceRegistry.h"

namespace Tmpl8
{
    void ForceRegistry::Add(const Rigidbody2D& rb, const ForceGenerator& fg)
    {
        auto* fr = new ForceRegistration(fg, rb);
        registry.push_back(fr);
    }

    void ForceRegistry::Remove(const Rigidbody2D& rb, const ForceGenerator& fg)
    {
        auto* fr = new ForceRegistration(fg, rb);
        registry.remove(fr);
    }

    void ForceRegistry::Clear()
    {
        registry.clear();
    }

    void ForceRegistry::UpdateForces(float dt) const
    {
        for (const auto fr : registry)
        {
            fr->fg.UpdateForce(fr->rb, dt);
        }
    }

    void ForceRegistry::ZeroForces() const
    {
        for (const auto fr : registry)
        {
            //fr->rb.ZeroForces;
        }
    }
}
