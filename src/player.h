#pragma once

#include "InputSystem.h"
#include "surface.h"
#include "template.h"

class AABB;

using namespace Tmpl8;

/*enum anims
{
    A_Idle,
    A_Walk,
    A_Jump
};*/


enum PlayerState
{
    S_Idle,
    S_Walk,
    S_Jump,
};

class Player
{
private:
    // LOOK FOR A PLACE TO PUT THESE
    /*unsigned int frame = 0;
    float animationTime{};
    float animationSpeed = .1f;*/
private:
    Sprite* sprite;
    InputSystem input;
    AABB* aabb;

    vec2 playerPosition{};
    
    // Input variables
    float horizontalInput{};
    // MovementVariables
    PlayerState currentState = S_Idle;
    float walkSpeed;
    float jumpForce;

    //bool isFacingRight;
public:
    Player();
    ~Player();

    void Update(float dt);
    void HandleJump();
    void HandleDirection();
    void HandleGravity();
    void ApplyMovement();
    void UpdatePhysics(float dt);
    void RenderPlayer(Surface* screen);
    void HandleAction(ActionType action);

    //void SwitchAnim(anims animToPlay);
    
private:
    //void FlipSprite();
    //void UpdateAnim(float dt);
    
};
