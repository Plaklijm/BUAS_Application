#pragma once
#include "forces/ForceRegistry.h"
#include "forces/Gravity.h"

namespace Tmpl8
{
    class PhysicsHandler
    {
    public:
        PhysicsHandler(float fixedUpdateDt, vec2 gravity);
        void UpdatePhysics(float dt);
        void FixedUpdate();
        void AddRigidbody(const Rigidbody2D& rb);
    private:
        ForceRegistry forceRegistry;
        std::list<Rigidbody2D> rigidbodies;
        Gravity gravity;
        float fixedUpdate;
        
    };
}
