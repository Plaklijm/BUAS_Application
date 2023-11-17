#pragma once
#include "../../template.h"

namespace Tmpl8
{
    
    class Rigidbody2D
    {
    public:
        vec2 GetPosition() const;
        void SetPosition(const vec2& newPosition);

        float GetMass() const;
        void SetMass(float mass);

        void PhysicsUpdate(float dt);

        void ClearAccum();
        void SyncCollider();

        void AddForce(vec2 force);
    private:
        vec2 rawPos = vec2();
        
        vec2 pos = vec2();
        vec2 vel;
        vec2 damp;
        float mass,invMass;

        vec2 accumForce;
        
    };
    
}
