#include "player.h"

#include <iostream>
#include <string>
#include "template.h"
#include "AABB.h"


// TODO: IMPLEMENT BETTER INPUT SYSTEM PLS USING THE COMMAND PATTERN :D

Player::Player() : PhysEntity()
{
    //currentAnim = IDLE;
    sprite = new Sprite(new Surface("assets/player/inhale_float.png"), 6);

    position = {40, ScreenHeight-50};
    
    vec2 halfsizeTemp{10,10};
    aabb = new AABB(position, halfsizeTemp);
    walkSpeed = 160.f;
    jumpForce = 400.f;
}

Player::~Player()
{
}

void Player::UpdatePhysics(float dt)
{
    PhysEntity::UpdatePhysics(dt);
}

void Player::RenderPlayer(Surface* screen)
{
    sprite->Draw(screen, position.x, position.y);
    
    std::string cs = std::to_string(currentState);
    char *ccs = new char[cs.length() + 1];
    strcpy(ccs, cs.c_str());
    screen->Print(ccs, 2, 10, 0xffffff);
}

void Player::UpdatePlayer(float dt)
{
    //printf("%i",onGround);
    switch (currentState)
    {
    case S_Idle:
        speed = {0,0};
        // Insert Anim logic; anim.play(idleanim)
        if (!onGround)
        {
            currentState = S_Jump;
            break;
        }

        if (moveLeft || moveRight)
        {
            currentState = S_Walk;
            break;
        }

        if (jump)
        {
            speed.y = jumpForce;
            currentState = S_Jump;
            break;
        }
        break;
    case S_Walk:
        // play walk anim
        /*if (!moveLeft || !moveRight)
        {
            currentState = S_Idle;
            speed = {0,0};
            break;
        }*/
        if (moveRight)
        {
            printf("leftw\n");
            if (pushesLeftWall)
                speed.x = 0;
            else
                speed.x = -walkSpeed;
            //flip sprite
        }
        if (moveLeft)
        {
            printf("rightw\n");
            if (pushesRightWall)
                speed.x = 0;
            else
                speed.x = walkSpeed;
            //flip sprite
        }

        if (jump)
        {
            speed.y = jumpForce;
            currentState = S_Jump;
            break;
        }
        if (!onGround)
        {
            currentState = S_Jump;
            break;
        }
        break;
    case S_Jump:
        // Play anim
        speed.y += 9.81f * dt;
        speed.y = max(speed.y, 10);
        
        if (!moveLeft || !moveRight)
        {
            currentState = S_Idle;
            speed = {0,0};
            break;
        }
        if (moveLeft)
        {
            printf("left\n");
            if (pushesLeftWall)
                speed.x = 0;
            else
                speed.x = -walkSpeed;
            //flip sprite
        } else if (moveRight)
        {
            printf("right\n");
            if (pushesRightWall)
                speed.x = 0;
            else
                speed.x = walkSpeed;
            //flip sprite
        }
        
        break;
    default:
        break;
    }

    UpdatePhysics(dt);

    UpdatePrevInputs();
    
    printf("%d, %d, %d\n", moveLeft, moveRight, jump);
}

#pragma region Input

void Player::KeyUpEvent(int key, bool isController)
{
    if (!isController)
    {
        if (key == 4) moveLeft = false;
        else if (key == 7) moveRight = false;
        else if (key == 44) jump = false;
    }
    else
    {
        
    }
}

void Player::KeyDownEvent(int key, bool isController)
{
    if (key == 4)
    {
        moveLeft = true;
    }
    else if (key == 7)
    {
        moveRight = true;
    }
    else if (key == 44)
    {
        jump = true;
    }
}

void Player::ControllerJoyStick(vec2 input)
{
    
}

void Player::UpdatePrevInputs()
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

