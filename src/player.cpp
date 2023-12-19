#include "player.h"

#include "BoxCollider.h"
#include "template.h"
#include "InputManager.h"
#include "PlayerStats.h"

// https://www.myphysicslab.com/engine2D/rigid-body-en.html

Player::Player(InputManager* input)
{
    pInput = input;
    stats = new PlayerStats();
    
    //currentAnim = IDLE;
    //sprite = new Sprite(new Surface("assets/player/inhale_float.png"), 6);

    position = {0, 0};
    velocity = {0, 0};
    gravity = {0, 9.81f};
}

Player::~Player()
{
    
}

void Player::Update(float dt)
{
    // Handle input
    if (pInput->KeyPressed(SDL_SCANCODE_D) == pInput->KeyPressed(SDL_SCANCODE_A))
    {
        horizontalInput = 0;
    }
    else if (pInput->KeyPressed(SDL_SCANCODE_A))
    {
        horizontalInput = -1;
    }
    else if (pInput->KeyPressed(SDL_SCANCODE_D))
    {
        horizontalInput = 1;
    }

    // TODO: Fix controller input and add Axis support for left right and crouch
    jumpDown = pInput->KeyDown(SDL_SCANCODE_SPACE);// || pInput->CButtonDown(SDL_CONTROLLER_BUTTON_X);
    jumpHeld = pInput->KeyPressed(SDL_SCANCODE_SPACE);// || pInput->CButtonPressed(SDL_CONTROLLER_BUTTON_X);

    sprintPressed = pInput->KeyPressed(SDL_SCANCODE_LSHIFT);// || pInput->CButtonPressed(SDL_CONTROLLER_BUTTON_A);

    crouchPressed = pInput->KeyPressed(SDL_SCANCODE_LCTRL);
}


void Player::UpdatePhysics(float dt)
{
    // Check Collision
    // Jump
    // 
    // Move player << gravity applied
    Move(dt);
}

void Player::RenderPlayer(Surface* screen)
{
    screen->Box(position.x, position.y, position.x + 64, position.y + 64, 0xffffff);
    /*std::string cs = std::to_string(currentState);
    char *ccs = new char[cs.length() + 1];
    strcpy(ccs, cs.c_str());
    screen->Print(ccs, 2, 10, 0xffffff);*/
}

void Player::Move(float dt)
{
    // Newton's second law
    velocity.x += horizontalInput * stats->GetAcceleration() * dt;
    velocity.x *= 1 - stats->GetGroundFriction() * dt;

    velocity.y += gravity.y * dt;
    
    LimitVelocity();
    printf("%f\n", velocity.x);

    // Apply the movement
    position += velocity * dt;
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
    if (abs(velocity.x) > stats->GetMaxVel().y)
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

