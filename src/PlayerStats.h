#pragma once

// Hardcoded stats of the player. These values never change and need to be set before compiling the game
// This is done this way to clean up the player class and to have a clear distinction between 'hard' values and 'soft' values
struct PlayerStats
{
public:
    // getters
    vec2 GetMinVel() const              { return minVel; }
    float GetMaxFallSpeed() const       { return maxFallSpeed; }
    float GetWalkSpeed() const          { return walkSpeed; }
    float GetSprintSpeed() const        { return sprintSpeed; }
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
    vec2            minVel              { 2.f, 0.f };
    float           maxFallSpeed        { 30.f };
    float           walkSpeed           { 3.5f };
    float           sprintSpeed         { 7.f };
    float           acceleration        { 80.f };
    float           fallAcceleration    { 75.f };
    float           groundFriction      { 40.f };
    float           airFriction         { 15.f };
    float           jumpForce           { -15.f };
    float           coyoteTime          { .15f };
    float           jumpBuffer          { .15f };
    float           mass                { 10.f };
    vec2            size                { 32, 32 };
};
