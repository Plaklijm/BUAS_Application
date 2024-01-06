#pragma once

#include "PlayerStats.h"
#include "../Engine/Actor.h"
#include "../Engine/template.h"
#include "../Engine/surface.h"

class InputManager;
class AnimationSystem;

using namespace Tmpl8;

/*enum anims
{
    A_Idle,
    A_Walk,
    A_Jump
};*/

class Player : public Actor
{
private:
    // LOOK FOR A PLACE TO PUT THESE
    /*unsigned int frame = 0;
    float animationTime{};
    float animationSpeed = .1f;*/
private:
    InputManager*               pInput;
    AnimationSystem*            anim;

    struct PlayerStats*         stats;

    // Input variables
    float                       horizontalInput{};
    bool                        jumpDown{};
    bool                        jumpHeld{};
    bool                        sprintPressed{};
    bool                        moveObjectPressed{};

    // movement variables
    vec2                        velocityAccumulator;
    vec2                        velocity;

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
    AnimationName               currentAnimState;

    int                         isJumping;

    timer                       stepTimer;
    float                       stepInterval;
    //bool isFacingRight;
public:
    Player(vec2 startPos, InputManager* input, World* world);
    ~Player();

    void Update(float dt);
    
    void UpdatePhysics(float dt);
    void RenderPlayer(Surface* screen);

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
