#include "player.h"

#include <iostream>

Player::Player() : PhysEntity()
{
    //currentAnim = IDLE;
    sprite = new Sprite(new Surface("assets/player/inhale_float.png"), 6);
}

Player::~Player()
{
}

void Player::UpdatePhysics(float dt)
{
    PhysEntity::UpdatePhysics(dt);
}

void Player::UpdatePlayer(float dt)
{
    //UpdateAnim(dt);
}

#pragma region Input

void Player::KeyUpEvent(int key, bool isController)
{
    
}

void Player::KeyDownEvent(int key, bool isController)
{
    
}

void Player::ControllerJoyStick(vec2 input)
{
    
}

#pragma endregion

/*void Player::SwitchAnim(anims animToPlay)
{
    switch (animToPlay)
    {
    case IDLE:
        break;
    case WALK:
        break;
    case CROUCH:
        break;
    default:
        std::cout << "ANIM WARNING: Anim does not exist" << std::endl;
        break;
    }
}*/

/*void Player::UpdateAnim(float dt)
{
    animationTime += dt;
    if (animationTime >= animationSpeed)
    {
        animationTime = 0;
        sprite->SetFrame(frame);
        frame++;
        if (frame >= sprite->Frames()) { frame = 0; }
    }
}*/

