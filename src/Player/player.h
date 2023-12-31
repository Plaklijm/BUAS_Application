#pragma once


#include "../Engine/Actor.h"
#include "../surface.h"
#include "../template.h"


namespace Tmpl8
{
    class InputManager;
}

class AABB;
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
    Sprite*                      sprite;
    AnimationSystem*            anim;

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

    float                       maxSpeedX;
    bool                        flipHorizontally;
    bool                        grounded{};
    
    bool                        isCrouched{};
    float                       oldCrouchPosition{};

    
    bool                        jumpToConsume{};
    bool                        bufferedJumpUsable{};
    bool                        endedJumpEarly{};
    bool                        coyoteUsable{};
    bool                        canDoubleJump{};
    float                       timeJumpWasPressed{};

    //bool isFacingRight;
public:
    Player(InputManager* input, World* world);
    ~Player();

    void Update(float dt);
    
    void UpdatePhysics(float dt);
    void RenderPlayer(Surface* screen);

private:
    void CalculateGravity(float dt);
    void HandleJump();
    
    void CalculateDirectionalMovement(float dt);
    void ApplyMovement();

    // Helper functions
    bool HasBufferedJump() const;
    bool CanUseCoyote() const;

    //void SwitchAnim(anims animToPlay);
    
private:
    //void FlipSprite();
    //void UpdateAnim(float dt);
    
};
