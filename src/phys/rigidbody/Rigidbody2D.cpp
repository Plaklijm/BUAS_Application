#include "Rigidbody2D.h"

namespace Tmpl8
{
    vec2 Rigidbody2D::GetPosition() const
    {
        return this->pos;
    }

    void Rigidbody2D::SetPosition(const vec2& newPosition)
    {
        this->pos = newPosition;
    }

    float Rigidbody2D::GetMass() const
    {
        return this->mass;
    }

    void Rigidbody2D::SetMass(float mass)
    {
        this->mass = mass;
        if (this->mass != 0.0f)
        {
            this->invMass = 1.0f / this->mass;
        }
    }

    void Rigidbody2D::PhysicsUpdate(float dt)
    {
        if (this->mass == 0.0f) return;

        // Calculate Vel
        auto accel = vec2(accumForce * this->invMass);
        this->vel += accel * dt;

        // Update Pos
        this->pos += vec2(vel * dt);

        SyncCollider();
        ClearAccum();
    }

    void Rigidbody2D::ClearAccum()
    {
        this->accumForce = vec2();
    }

    void Rigidbody2D::SyncCollider()
    {
        if (this->rawPos.x != 0 && this->rawPos.y != 0)
        {
            this->rawPos = this->pos;
        }
    }

    void Rigidbody2D::AddForce(vec2 force)
    {
        this->accumForce += force;
    }
}
