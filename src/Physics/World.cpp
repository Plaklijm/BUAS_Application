#include "World.h"

#include "Arbiter.h"
#include "Body.h"

//----------------------------------------------------------------------------------------------------------------------
// Broadphase with Slow O(N^2). This isnt performant at all, but for now its good enough, this could be replaced with
// an AABB tree, a grid or any other optimization technique.
//----------------------------------------------------------------------------------------------------------------------

void World::BroadPhase()
{
    for (int i = 0; i < (int)bodies.size(); ++i)
    {
        Body* bi = bodies[i];

        for (int j = i + 1; j < (int)bodies.size(); ++j)
        {
            Body* bj = bodies[j];

            // Skip if the two bodies are both static
            if (bi->invMass == 0.f && bj->invMass == 0.f)
                continue;

            Arbiter newArb{bi, bj}; // <<<<< this performs the narrow phase collision (need to look at source for this)
            ArbiterKey key{bi, bj};

            if (newArb.numContacts > 0)
            {
                ArbIter iter = arbiters.find(key);
                if (iter == arbiters.end())
                    arbiters.insert(ArbPair(key, newArb));
                else
                    iter->second.Update(newArb.contacts, newArb.numContacts);
            }
            else
            {
                arbiters.erase(key);
            }
        }
    }
}

void World::ApplyForces(float dt)
{
    for (auto body : bodies)
    {
        // skip if the body is static (no forces need to be applied)
        if (body->invMass == 0.f)
            continue;

        // Newtons second law (F = ma)
        body->velocity += (body->force * (gravity + body->invMass)) * dt;
    }
}

void World::UpdatePositions(float dt)
{
    for (auto body : bodies)
    {
        // set the position based on the velocity
        body->position += body->velocity * dt;

        // zero out the force so that it can be calculated next frame
        body->force = vec2::Zero();
    }
}
