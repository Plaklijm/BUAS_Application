#pragma once
#include <map>

// Hardcoded stats of the player. These values never change and need to be set before compiling the game
// This is done this way to clean up the player class and to have a clear distinction between 'hard' values and 'soft' values


// ANIMATION
enum AnimationName
{
    WALK = 0,
    RUN,
    IDLE,
    JUMP,
    DOUBLEJUMP,
    COLLECT,
    PUSH,
    PULL
};

// GENERAL STATS AND ALL THE GETTERS AND SETTERS
struct PlayerStats
{
public:
    // getters
    float GetMaxFallSpeed() const       { return maxFallSpeed; }
    float GetWalkSpeed() const          { return walkSpeed; }
    float GetSprintSpeed() const        { return sprintSpeed; }
    float GetAcceleration() const       { return acceleration; }
    float GetFallAcceleration() const   { return fallAcceleration; }
    float GetGroundFriction() const     { return groundFriction; }
    float GetAirFriction() const        { return airFriction; }
    float GetJumpForce() const          { return jumpForce; }
    float GetDoubleJumpForce() const    { return doubleJumpForce; }
    float GetCoyoteTime() const         { return coyoteTime; }
    float GetJumpBuffer() const         { return jumpBuffer; }
    
    float GetAnimRate() const           { return animRate; }
    float GetSpriteOffset() const       { return spriteOffset; }

private:
    // Statistics of the player movement
    // TODO: Figure out the variable amount of each one
    float           maxFallSpeed        { 16.5f };
    float           walkSpeed           { 2.f };
    float           sprintSpeed         { 5.f };
    float           acceleration        { 60.f };
    float           fallAcceleration    { 60.f };
    float           groundFriction      { 50.f };
    float           airFriction         { 20.f };
    float           jumpForce           { -14.f };
    float           doubleJumpForce     { -12.f };
    float           coyoteTime          { .15f };
    float           jumpBuffer          { .15f };

    float           animRate            { 90.f };
    float           spriteOffset        { 10.f };
};
