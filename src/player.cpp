#include "player.h"

#include <algorithm>
#include "BoxCollider.h"
#include "template.h"
#include "InputManager.h"
#include "PlayerStats.h"

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

#include "World.h"

// https://www.myphysicslab.com/engine2D/rigid-body-en.html

Player::Player(InputManager* input, World* world) : Actor(vec2(32,0), vec2(32,32), world)
{
    pInput = input;
    stats = new PlayerStats();
    //currentAnim = IDLE;
    //sprite = new Sprite(new Surface("assets/player/inhale_float.png"), 6);
    
    velocityAccumulator = {0, 0};
    gravity = {0, .981f};
}

Player::~Player()
{
    
}

float time;
float frameLeftGrounded = std::numeric_limits<float>().lowest();

void Player::Update(float dt)
{
    time += dt;
    // Handle input
    left = pInput->KeyPressed(SDL_SCANCODE_A);
    right = pInput->KeyPressed(SDL_SCANCODE_D);
    // Set the horizontal input to -1 if left 1 if right and 0 if both left and right are pressed
    horizontalInput = right - left;

    // TODO: Fix controller input and add Axis support for left right and crouch
    jumpDown = pInput->KeyDown(SDL_SCANCODE_SPACE);
    jumpHeld = pInput->KeyPressed(SDL_SCANCODE_SPACE);

    sprintPressed = pInput->KeyPressed(SDL_SCANCODE_LSHIFT);

    crouchPressed = pInput->KeyPressed(SDL_SCANCODE_LCTRL);

    if (jumpDown)
    {
        jumpToConsume = true;
        timeJumpWasPressed = time;
    }

    if (GetCollisionNormal().y > 0)
    {
        grounded = true;
        coyoteUsable = true;
        bufferedJumpUsable = true;
        endedJumpEarly = false;
    }
    else
    {
        grounded = false;
        frameLeftGrounded = time;
    }
}



vec2 result;
void Player::UpdatePhysics(float dt)
{
    // Jump
    // 
    // Move player << gravity applied
    CalculateGravity(dt);
    HandleJump();
    CalculateDirectionalMovement(dt);
    ApplyMovement();
}

void Player::CalculateGravity(float dt)
{
    if (grounded)// && velocityAccumulator.y <= 0.f)
    {
        velocityAccumulator.y = 1.f;
    }
    else
    {
        auto inAirGravity = stats->GetFallAcceleration();
        if (endedJumpEarly && velocityAccumulator.y > 0)
            inAirGravity *= 3;
        
        if (abs(stats->GetMaxVel().y - velocityAccumulator.y) <= inAirGravity * dt)
            velocityAccumulator.y = stats->GetMaxVel().y;
        else
            velocityAccumulator.y += sgn(stats->GetMaxVel().y - velocityAccumulator.y) * (inAirGravity * dt);
    }
}

void Player::RenderPlayer(Surface* screen)
{
    auto b1 = GetCollider()->GetHitBox();
    screen->Box(b1.x, b1.y, b1.x + b1.w, b1.y + b1.h, 0xffffff);
    
    /*std::string cs = std::to_string(currentState);
    char *ccs = new char[cs.length() + 1];
    strcpy(ccs, cs.c_str());
    screen->Print(ccs, 2, 10, 0xffffff);*/
}

bool Player::HasBufferedJump() const
{
    return bufferedJumpUsable && time < timeJumpWasPressed + stats->GetJumpBuffer();
}

bool Player::CanUseCoyote() const
{
    return coyoteUsable && !grounded && time < frameLeftGrounded + stats->GetCoyoteTime();
}

void Player::HandleJump()
{
    if (!endedJumpEarly && !grounded && !jumpHeld && velocity.y > 0)
        endedJumpEarly = true;

    if (!jumpToConsume && !HasBufferedJump())
        return;
    
    if (grounded || CanUseCoyote()) 
    {
        endedJumpEarly = false;
        timeJumpWasPressed = 0;
        bufferedJumpUsable = false;
        coyoteUsable = false;
        velocityAccumulator.y = stats->GetJumpForce();
    }

    jumpToConsume = false;
}

void Player::CalculateDirectionalMovement(float dt)
{
    // TODO: Fix jittre
    if (horizontalInput == 0)
    {
        // Get the appropriate deceleration factor
        auto decel = grounded ? stats->GetGroundFriction() : stats->GetAirFriction();
        // Add to the velocity by a fixed amount depending on the step size (decel * dt)
        if (abs(0 - velocityAccumulator.x) <= decel * dt)
            velocityAccumulator.x = 0;
        else
            velocityAccumulator.x += sgn(0 - velocityAccumulator.x) * (decel * dt);
    }
    else
    {
        if (abs((horizontalInput * stats->GetMaxVel().x) - velocityAccumulator.x) <= stats->GetAcceleration() * dt)
            velocityAccumulator.x = (horizontalInput * stats->GetMaxVel().x);
        else
            velocityAccumulator.x += sgn((horizontalInput * stats->GetMaxVel().x) - velocityAccumulator.x) * (stats->GetAcceleration() * dt);
    }
}



void Player::ApplyMovement()
{
    velocity = velocityAccumulator;
    MoveX(velocity.x);
    MoveY(velocity.y);
    
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
    if (abs(velocityAccumulator.x) < stats->GetMinVel().x)
        velocityAccumulator.x = 0;
    
    // Set max velocity in X dimension based on direction
    if (abs(velocityAccumulator.x) > stats->GetMaxVel().x)
        velocityAccumulator.x = stats->GetMaxVel().x * (velocityAccumulator.x < 0.f ? -1.f : 1.f);

    // Set max velocity in Y dimension based on direction, this will also limit the fall speed
    if (abs(velocityAccumulator.y) > stats->GetMaxVel().y)
        velocityAccumulator.y = stats->GetMaxVel().y * (velocityAccumulator.y < 0.f ? -1.f : 1.f);
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

