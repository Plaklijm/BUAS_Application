#include "player.h"

#include <algorithm>

#include "BoxCollider.h"
#include "template.h"
#include "InputManager.h"
#include "PlayerStats.h"
#include "Collision.h"


#include "World.h"

// https://www.myphysicslab.com/engine2D/rigid-body-en.html

Player::Player(InputManager* input, World* world) : Actor(vec2(32,0), vec2(32,32), world)
{
    pInput = input;
    stats = new PlayerStats();
    //currentAnim = IDLE;
    //sprite = new Sprite(new Surface("assets/player/inhale_float.png"), 6);

    position = {32, 0};
    velocity = {0, 0};
    gravity = {0, .981f / 2};
    collider = new BoxCollider(position, stats->GetSize());
}

Player::~Player()
{
    
}

void Player::Update(float dt)
{
    // Handle input
    /*if (pInput->KeyPressed(SDL_SCANCODE_D) == pInput->KeyPressed(SDL_SCANCODE_A))
    {
        horizontalInput = 0;
    }*/
    left = pInput->KeyPressed(SDL_SCANCODE_A);
    right = pInput->KeyPressed(SDL_SCANCODE_D);
    horizontalInput = right - left;

    // TODO: Fix controller input and add Axis support for left right and crouch
    jumpDown = pInput->KeyDown(SDL_SCANCODE_SPACE);// || pInput->CButtonDown(SDL_CONTROLLER_BUTTON_X);
    jumpHeld = pInput->KeyPressed(SDL_SCANCODE_SPACE);// || pInput->CButtonPressed(SDL_CONTROLLER_BUTTON_X);

    sprintPressed = pInput->KeyPressed(SDL_SCANCODE_LSHIFT);// || pInput->CButtonPressed(SDL_CONTROLLER_BUTTON_A);

    crouchPressed = pInput->KeyPressed(SDL_SCANCODE_LCTRL);
}


    vec2 result;
void Player::UpdatePhysics(float dt)
{
    // Check Collision
    //bool collide = Collision::RectIntersectAt(&collider->GetHitBox(), vec2(0, 50), &testCollision->hitBox->GetHitBox(), result); //SDL_IntersectRect(&collider->GetHitBox(), &testCollision->hitBox->GetHitBox(), &result);
    
    // Jump
    // 
    // Move player << gravity applied
    
    Move(dt);
    
}

void Player::RenderPlayer(Surface* screen)
{
    collider->SetPosition(position);
    auto b1 = collider->GetHitBox();
    screen->Box(b1.x, b1.y, b1.x + b1.w, b1.y + b1.h, 0xffffff);
    
    /*std::string cs = std::to_string(currentState);
    char *ccs = new char[cs.length() + 1];
    strcpy(ccs, cs.c_str());
    screen->Print(ccs, 2, 10, 0xffffff);*/
}

void Player::Move(float dt)
{
    auto speedX = 5 * horizontalInput;
    auto speedY = 0.f;
    speedY = std::min(speedY+gravity.y, stats->GetMaxVel().y);

    MoveX(speedX);
    MoveY(speedY);

    position = GetPosition();
    //printf("X = %f, Y = %f\n", speedX, speedY);
    /*if (jumpDown)
    {
        velocity.y = 200;
        printf("JUMP");
    }
    
    // Newton's second law
    velocity.x += horizontalInput * stats->GetAcceleration() * dt;
    velocity.x *= 1 - stats->GetGroundFriction() * dt;

    velocity.y += gravity.y * stats->GetAcceleration() * dt;
    
    LimitVelocity();

    if (!SDL_IntersectRect(&collider->GetHitBox(), &testCollision->hitBox->GetHitBox(), &result))
    {
        position += velocity * dt;
    }
    else
    {
        position.x += velocity.x * dt;
    }*/
    // Apply the movement
}

void Player::LimitVelocity()
{
    // Set min velocity in X dimension
    // When subtracting the friction it'll get infinitely smaller, so this makes sure to put the vel at 0 
    if (abs(velocity.x) < stats->GetMinVel().x)
        velocity.x = 0;
    
    // Set max velocity in X dimension based on direction
    if (abs(velocity.x) > stats->GetMaxVel().x)
        velocity.x = stats->GetMaxVel().x * (velocity.x < 0.f ? -1.f : 1.f);

    // Set max velocity in Y dimension based on direction, this will also limit the fall speed
    if (abs(velocity.y) > stats->GetMaxVel().y)
        velocity.y = stats->GetMaxVel().y * (velocity.y < 0.f ? -1.f : 1.f);
}

void Player::ApplyForce(vec2 inputForce)
{
    force += inputForce * stats->GetInvMass();
}

void Player::ApplyGravity()
{
    
}

void Player::ApplyFriction(vec2 friction)
{
    
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

