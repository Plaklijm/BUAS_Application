﻿#pragma once
#include <vector>

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

    // MovementVariables
    PlayerState currentState = S_Idle;
    float walkSpeed;
    float jumpForce;
    
protected:
    std::vector<bool> currInput;
    std::vector<bool> prevInput;


    
protected:
    bool Released(int key);
    bool KeyState(int key);
    bool Pressed(int key);
    
public:
    Player();
    ~Player() override;

    void UpdatePlayer(float dt);
    //void SwitchAnim(anims animToPlay);

    void KeyUpEvent(int key, bool isController);
    void KeyDownEvent(int key, bool isController);
    void ControllerJoyStick(vec2 input);
    void UpdatePrevInputs();

    // TEMP
    bool moveRight = false; // 7
    bool moveLeft = false; // 4
    bool jump = false; // 44
    
private:
    //void UpdateAnim(float dt);

public:
    void UpdatePhysics(float dt) override;
    void RenderPlayer(Surface* screen);
};
