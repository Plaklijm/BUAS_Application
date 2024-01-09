#pragma once

// Hardcoded stats of the player. These values never change and need to be set before compiling the game
// This is done this way to clean up the player class and to have a clear distinction between 'hard' values and 'soft' values

// ANIMATION
enum AnimationName
{
    a_WALK = 0,
    a_RUN,
    a_IDLE,
    a_JUMP,
    a_DOUBLEJUMP,
    a_COLLECT,
    a_PUSH,
    a_PULL,
    a_LAND
};

// GENERAL STATS AND ALL THE GETTERS AND SETTERS
struct PlayerStats
{
    // OOEHF Looks nice :>              Learned this technique from the source of Doom III and got stuck with it ever since   
public:
    // Getters
    float GetMaxFallSpeed() const       { return maxFallSpeed; }
    float GetWalkSpeed() const          { return walkSpeed; }
    float GetSprintSpeed() const        { return sprintSpeed; }
    float GetPushPullSpeed() const      { return pushPullSpeed; }
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
    // If you want to change how the player behaves/feels these are the only values you'd have to change
    float           maxFallSpeed        { 16.5f };
    float           walkSpeed           { 2.f };
    float           sprintSpeed         { 5.f };
    float           pushPullSpeed       { 1.f };
    float           acceleration        { 60.f };
    float           fallAcceleration    { 45.f };
    float           groundFriction      { 50.f };
    float           airFriction         { 30.f };
    float           jumpForce           { -11.f };
    float           doubleJumpForce     { -10.f };
    float           coyoteTime          { .15f };
    float           jumpBuffer          { .15f };

    float           animRate            { 90.f };
    float           spriteOffset        { 10.f };
};
