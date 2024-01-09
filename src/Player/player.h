#pragma once

#include "PlayerStats.h"
#include "../Engine/Actor.h"
#include "../Engine/template.h"

class InputManager;
class AnimationSystem;

class Player : public Actor
{
private:
    // Im pretty proud of how neat this all looks :)
    InputManager*               pInput;
    AnimationSystem*            anim;

    PlayerStats*                stats;

    // Input variables
    float                       horizontalInput{};
    bool                        jumpDown{};
    bool                        jumpHeld{};
    bool                        sprintPressed{};
    bool                        moveObjectPressed{};

    // movement variables
    Tmpl8::vec2                 velocityAccumulator;
    Tmpl8::vec2                 velocity;

    float                       maxSpeedX;
    bool                        flipHorizontally;
    bool                        grounded{};
    bool                        landed{};
    
    bool                        jumpToConsume{};
    bool                        bufferedJumpUsable{};
    bool                        endedJumpEarly{};
    bool                        coyoteUsable{};
    bool                        canDoubleJump{};
    float                       timeJumpWasPressed{};
    bool                        collect;

    bool                        isPushingObj{};
    bool                        isPullingObj{};
    SDL_Rect                    pushCol;

    AnimationName               currentAnimState;

    int                         isJumping{};

    Tmpl8::timer                stepTimer;
    float                       stepInterval;
    
public:
    Player(Tmpl8::vec2 startPos, InputManager* input, World* world);
    ~Player() = default;

    void SetMaxSpeed();
    void SetGrounded();
    void HandleInput();
    void Update(float dt);
    
    void UpdatePhysics(float dt);
    void RenderPlayer(Tmpl8::Surface* screen) const;

    void Collect();
private:
    void HandleAnimations();

    void HandlePushObj();
    
    void CalculateGravity(float dt);
    void HandleJump();
    
    void CalculateDirectionalMovement(float dt);
    void ApplyMovement();

    // Helper functions
    bool HasBufferedJump() const;
    bool CanUseCoyote() const;
};
