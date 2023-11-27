#pragma once
#include <vector>

#include "InputSystem.h"
#include "PhysEntity.h"
#include "surface.h"

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

class Player : public PhysEntity
{
private:
    // LOOK FOR A PLACE TO PUT THESE
    /*unsigned int frame = 0;
    float animationTime{};
    float animationSpeed = .1f;*/
private:
    Sprite* sprite;
    InputSystem input;

    // Input variables
    float horizontalInput;
    // MovementVariables
    PlayerState currentState = S_Idle;
    float walkSpeed;
    float jumpForce;

    //bool isFacingRight;
public:
    Player();
    ~Player() override;

    void Update(float dt);
    void UpdatePhysics(float dt) override;
    void RenderPlayer(Surface* screen);
    
    //void SwitchAnim(anims animToPlay);
    
private:
    //void FlipSprite();
    //void UpdateAnim(float dt);
    
};
