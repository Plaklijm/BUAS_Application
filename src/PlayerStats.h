#pragma once

struct PlayerStats
{
public:
    // getters
    vec2 GetMaxVel() const              { return maxVel; }
    vec2 GetMinVel() const              { return minVel; }
    float GetAcceleration() const       { return acceleration; }
    float GetFallAcceleration() const   { return fallAcceleration; }
    float GetGroundFriction() const     { return groundFriction; }
    float GetAirFriction() const        { return airFriction; }
    float GetJumpForce() const          { return jumpForce; }
    float GetCoyoteTime() const         { return coyoteTime; }
    float GetJumpBuffer() const         { return jumpBuffer; }
    float GetMass() const               { return mass; }
    float GetInvMass() const            { return 1 / mass; }
    vec2 GetSize() const                { return size; }

private:
    // Statistics of the player movement
    // TODO: Figure out the variable amount of each one
    vec2            maxVel              { 7.5f, 12.5f };
    vec2            minVel              { 2.f, 0.f };
    float           acceleration        { 100.f };
    float           fallAcceleration    { 125.f };
    float           groundFriction      { 50.f };
    float           airFriction         { 30.f };
    float           jumpForce           { -25.f };
    float           coyoteTime          { .15f };
    float           jumpBuffer          { .15f };
    float           mass                { 10.f };
    vec2            size                { 32, 32 };
};
