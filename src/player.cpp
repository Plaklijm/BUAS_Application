#include "player.h"

#include <iostream>
#include <string>
#include "template.h"
#include "AABB.h"
#include "InputSystem.h"


// TODO: IMPLEMENT BETTER INPUT SYSTEM PLS USING THE COMMAND PATTERN :D

Player::Player() : PhysEntity()
{
    input = InputSystem::instance();
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

void Player::RenderPlayer(Surface* screen)
{
    sprite->Draw(screen, position.x, position.y);
    
    std::string cs = std::to_string(currentState);
    char *ccs = new char[cs.length() + 1];
    strcpy(ccs, cs.c_str());
    screen->Print(ccs, 2, 10, 0xffffff);
}

void Player::Update(float dt)
{

    if (input.KeyDown(SDL_SCANCODE_A))       horizontalInput = -1;
    else if (input.KeyDown(SDL_SCANCODE_D))  horizontalInput = 1;
    else                                                horizontalInput = 0;

    //printf("%f\n", horizontalInput);

    if (input.KeyDown(SDL_SCANCODE_SPACE))
    {
        speed.y = jumpForce * dt;
        printf("JUMP");
    }
    
    /*printf("%i",onGround);
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

        if (input.KeyDown(SDL_SCANCODE_A) != input.KeyDown(SDL_SCANCODE_D))
        {
            printf("Go to walk\n");
            currentState = S_Walk;
            break;
        }

        if (input.KeyPressed(SDL_SCANCODE_SPACE))
        {
            printf("Go to Jump\n");
            speed.y = jumpForce;
            currentState = S_Jump;
            break;
        }
        break;
    case S_Walk:
        printf("Walk state\n");
        // play walk anim
        /*if (!moveLeft || !moveRight)
        {
            currentState = S_Idle;
            speed = {0,0};
            break;
        }#1#
        if (input.KeyPressed(SDL_SCANCODE_A) != input.KeyPressed(SDL_SCANCODE_D))
        {
            printf("back to idle state\n");
            currentState = S_Idle;
            speed = vec2::Zero();
            break;
        }
        if (input.KeyPressed(SDL_SCANCODE_D))
        {
            printf("leftw\n");
            if (pushesLeftWall)
                speed.x = 0;
            else
                speed.x = walkSpeed;
            //flip sprite
        }
        if (input.KeyPressed(SDL_SCANCODE_A))
        {
            printf("rightw\n");
            if (pushesRightWall)
                speed.x = 0;
            else
                speed.x = -walkSpeed;
            //flip sprite
        }

        if (input.KeyPressed(SDL_SCANCODE_SPACE))
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
        
        if (!input.KeyPressed(SDL_SCANCODE_A) == !input.KeyPressed(SDL_SCANCODE_D))
        {
            speed = vec2::Zero();
        } else if (input.KeyPressed(SDL_SCANCODE_D))
        {
            //printf("right\n");
            if (pushesRightWall)
                speed.x = 0;
            else
                speed.x = walkSpeed;
            //flip sprite
        } else if (input.KeyPressed(SDL_SCANCODE_A))
        {
            //printf("left\n");
            if (pushesLeftWall)
                speed.x = 0;
            else
                speed.x = -walkSpeed;
            //flip sprite
        }

        if (onGround)
        {
            //if there's no movement change state to standing 
            if (input.KeyPressed(SDL_SCANCODE_A) == input.KeyPressed(SDL_SCANCODE_D))
            {
                currentState = S_Idle;
                speed = vec2::Zero();
            }
            else    //either go right or go left are pressed so we change the state to walk
            {
                currentState = S_Walk;
                speed.y = 0.0f;
            }
        }
        break;
    default:
        break;
    }*/
    
}

void Player::UpdatePhysics(float dt)
{
    speed.x = horizontalInput * walkSpeed;

    
    PhysEntity::UpdatePhysics(dt);
}

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

