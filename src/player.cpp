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

    position = {0, 0};

    const vec2 size{64,64};
    aabb = new AABB(position, size);
    walkSpeed = 160.f;
    jumpForce = 400.f;
    SetMass(.001);
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

void Player::IntegrateForces()
{
    if (this->invMass != 0)
    {
        this->velocity.x += (this->force.x * this->invMass) / 2;
        this->velocity.y += (this->force.y * this->invMass + gravity) / 2;
    }
}

void Player::IntegrateVelocity(float dt)
{
    if (this->invMass != 0)
    {
        this->position += this->velocity * dt;
        this->IntegrateForces();
    }
}

void Player::ApplyForce(const vec2 inputForce)
{
    this->force = inputForce;
}

void Player::ApplyImpulse(const vec2 impulseForce)
{
    this->velocity.x += this->invMass * impulseForce.x;
    this->velocity.y += this->invMass * impulseForce.y;
}

void Player::ClearForces()
{
    this->force = vec2::Zero();
}

void Player::SetMass(float mass)
{
    this->mass = mass;
    this->invMass = 1 / mass;
}

void Player::UpdatePhysics(float dt)
{
    IntegrateForces();
    IntegrateVelocity(dt);

    printf("x = %f, y = %f\n", position.x, position.y);
    aabb->pos = position;
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

