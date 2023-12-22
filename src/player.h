#pragma once


#include "Actor.h"
#include "surface.h"
#include "template.h"

namespace Tmpl8
{
    class InputManager;
}

class AABB;

using namespace Tmpl8;

/*enum anims
{
    A_Idle,
    A_Walk,
    A_Jump
};*/


constexpr float gravity {.0001};

class Player : public Actor
{
private:
    // LOOK FOR A PLACE TO PUT THESE
    /*unsigned int frame = 0;
    float animationTime{};
    float animationSpeed = .1f;*/
private:
    InputManager*               pInput;
    Sprite*                     sprite;

    struct PlayerStats*         stats;

    // Input variables
    float                       horizontalInput{};
    bool                        jumpDown{};
    bool                        jumpHeld{};
    bool                        sprintPressed{};
    bool                        crouchPressed{};
    bool                        left{};
    bool                        right{};

    // movement variables
    vec2                        velocityAccumulator;
    vec2                        velocity;
    vec2                        gravity;

    bool                        flipHorizontally;
    bool                        grounded{};

    bool                        jumpToConsume{};
    bool                        bufferedJumpUsable{};
    bool                        endedJumpEarly{};
    bool                        coyoteUsable{};
    float                       timeJumpWasPressed{};

    //bool isFacingRight;
public:
    Player(InputManager* input, World* world);
    ~Player();

    void Update(float dt);
    
    void CalculateGravity(float dt);
    void HandleJump();
    void CalculateDirectionalMovement(float dt);
    void ApplyMovement();
    void LimitVelocity();

    void UpdatePhysics(float dt);
    void RenderPlayer(Surface* screen);
    bool HasBufferedJump() const;
    bool CanUseCoyote() const;

    //void SwitchAnim(anims animToPlay);
    
private:
    //void FlipSprite();
    //void UpdateAnim(float dt);
    
};
