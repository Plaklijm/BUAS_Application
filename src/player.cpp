#include "player.h"

#include <iostream>
#include <string>
#include "template.h"
#include "AABB.h"
#include "InputSystem.h"

Player::Player()
{
    //currentAnim = IDLE;
    //sprite = new Sprite(new Surface("assets/player/inhale_float.png"), 6);

    playerPosition = {0, 0};
    
    vec2 size{64,64};
    aabb = new AABB(playerPosition, size);
    walkSpeed = 160.f;
    jumpForce = 400.f;
}

Player::~Player()
{
}

void Player::RenderPlayer(Surface* screen)
{
    screen->Box(int(aabb->pos.x),int(aabb->pos.y),int(aabb->pos.x + aabb->size.x),int(aabb->pos.y + aabb->size.y),0xffffff);
    
    std::string cs = std::to_string(currentState);
    char *ccs = new char[cs.length() + 1];
    strcpy(ccs, cs.c_str());
    screen->Print(ccs, 2, 10, 0xffffff);
}

void Player::HandleAction(ActionType action)
{
    switch (action) {
    case  ActionType::NO_MOVEMENT:
        printf("IDLE\n");
        horizontalInput = 0;
        break;
    case ActionType::MOVE_LEFT:
        printf("LEFT\n");
        horizontalInput = -1;
        break;
    case ActionType::MOVE_RIGHT:
        printf("RIGHT\n");
        horizontalInput = 1;
        break;
    case ActionType::JUMP:
        printf("JUMP\n");
        break;
    case ActionType::SPRINT:
        printf("SPRINT\n");
        break;
    default: break;
    }
}

void Player::Update(float dt)
{
    
}

void Player::HandleJump()
{
}

void Player::HandleDirection()
{
}

void Player::HandleGravity()
{
}

void Player::ApplyMovement()
{
}

void Player::UpdatePhysics(float dt)
{
    HandleJump();
    HandleDirection();
    HandleGravity();

    ApplyMovement();

    
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

