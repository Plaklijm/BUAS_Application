#include "PhysicsHandler.h"

namespace Tmpl8
{
    PhysicsHandler::PhysicsHandler(float fixedUpdateDt, vec2 gravity)
    {
        forceRegistry = ForceRegistry();
        this->gravity = Gravity(gravity);
        this->fixedUpdate = fixedUpdateDt;
    }

    void PhysicsHandler::UpdatePhysics(float dt)
    {

    }

    void PhysicsHandler::FixedUpdate()
    {
        forceRegistry.UpdateForces(fixedUpdate);

        // Update all the velocities of every registered rigidbody
        for (auto body : rigidbodies)
        {
            body.PhysicsUpdate(fixedUpdate);
        }
    }

    void PhysicsHandler::AddRigidbody(const Rigidbody2D& rb)
    {
        this->rigidbodies.push_back(rb);
        this->forceRegistry.Add(rb, gravity);
    }
}
