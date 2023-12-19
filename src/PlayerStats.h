#pragma once

struct PlayerStats
{
public:
    // getters
    vec2 GetMaxVel() const          { return maxVel; }
    vec2 GetMinVel() const          { return minVel; }
    float GetAcceleration() const   { return acceleration; }
    float GetGroundFriction() const    { return groundFriction; }
    float GetAirFriction() const       { return airFriction; }
    float GetJumpForce() const      { return jumpForce; }
    float GetCoyoteTime() const     { return coyoteTime; }
    float GetMass() const           { return mass; }
    float GetInvMass() const        { return 1 / mass; }
    vec2 GetHalfSize() const        { return halfSize; }

private:
    // Statistics of the player movement
    // TODO: Figure out the variable amount of each one
    vec2            maxVel          { 50.f, 60.f };
    vec2            minVel          { 2.f, 0.f };
    float           acceleration    { 350.f };
    float           groundFriction  { .925f};
    float           airFriction;
    float           jumpForce;
    float           coyoteTime;
    float           mass            { 10.f };
    vec2            halfSize        { 32, 32 };
};
