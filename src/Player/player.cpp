#include "player.h"

#include <algorithm>

#include "../Animation/AnimationSystem.h"
#include "../Engine/BoxCollider.h"
#include "../template.h"
#include "InputManager.h"
#include "PlayerStats.h"

// https://www.myphysicslab.com/engine2D/rigid-body-en.html

Player::Player(InputManager* input, World* world) : Actor(vec2(32,0), vec2(28,40), world)
{
    stats = new PlayerStats();

    pInput = input;

    // Initialize Animation
    anim = new AnimationSystem(stats->GetAnimRate());
    anim->AddAnim(IDLE, std::make_unique<Animation>(new Sprite(new Surface("assets/player/Character Idle 48x48.png"), 10), stats->GetAnimRate()));
    anim->AddAnim(WALK, std::make_unique<Animation>(new Sprite(new Surface("assets/player/PlayerWalk 48x48.png"), 8), stats->GetAnimRate()));
    anim->AddAnim(RUN, std::make_unique<Animation>(new Sprite(new Surface("assets/player/run cycle 48x48.png"), 8), stats->GetAnimRate()));
    anim->AddAnim(JUMP, std::make_unique<Animation>(new Sprite(new Surface("assets/player/player jump 48x48.png"), 3), stats->GetAnimRate(), false));
    anim->AddAnim(DOUBLEJUMP, std::make_unique<Animation>(new Sprite(new Surface("assets/player/player air spin 48x48.png"), 6), stats->GetAnimRate(), false));

    anim->SetCurrentAnim(IDLE);
    //sprite->SetFrame(0);
    velocityAccumulator = {0, 0};
    //gravity = {0, .981f};
    canDoubleJump = true;
}

Player::~Player()
{
    
}

float time;
float frameLeftGrounded = std::numeric_limits<float>::lowest();

int currentFrame;
int currentAnimFrameCount;

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
    
    if (left)
    {
        flipHorizontally = true;
        if (!sprintPressed && grounded && !jumpDown)
        {
            anim->SetCurrentAnim(RUN);
        }
    }
    else if (right)
    {
        flipHorizontally = false;
        if (!sprintPressed && grounded && !jumpDown)
        {
            anim->SetCurrentAnim(RUN);
        }
    }
    
    if (sprintPressed)
    {
        maxSpeedX = stats->GetWalkSpeed();
        anim->SetCurrentAnim(WALK);
    }
    else
        maxSpeedX = stats->GetSprintSpeed();
    
    if (jumpDown)
    {
        jumpToConsume = true;
        timeJumpWasPressed = time;
    }

    if (GetCollisionNormal().y > 0)
    {
        if (!horizontalInput)
        {
            anim->SetCurrentAnim(IDLE);
        }
        grounded = true;
        coyoteUsable = true;
        bufferedJumpUsable = true;
        endedJumpEarly = false;
        canDoubleJump = false;
    }
    else if (GetCollisionNormal().y < 0)
    {
        // If you hit an ceiling zero out the velocity
        velocityAccumulator.y = 0;
    }
    else
    {
        grounded = false;
        frameLeftGrounded = time;
    }
    anim->Update();
}

void Player::UpdatePhysics(float dt)
{
    CalculateGravity(dt);
    HandleJump();
    CalculateDirectionalMovement(dt);
    ApplyMovement();
}

void Player::RenderPlayer(Surface* screen)
{
    const auto b1 = GetCollider()->GetHitBox();
    screen->Box(b1.x, b1.y, b1.x + b1.w, b1.y + b1.h, 0xffffff);

    anim->Render(screen, GetPosition().x - stats->GetSpriteOffset(), GetPosition().y, flipHorizontally);
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
        
        if (abs(stats->GetMaxFallSpeed() - velocityAccumulator.y) <= inAirGravity * dt)
            velocityAccumulator.y = stats->GetMaxFallSpeed();
        else
            velocityAccumulator.y += sgn(stats->GetMaxFallSpeed() - velocityAccumulator.y) * (inAirGravity * dt);
    }
}


#pragma region Jump
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
    
    if (grounded && jumpToConsume || CanUseCoyote() || canDoubleJump) 
    {
        endedJumpEarly = false;
        timeJumpWasPressed = 0;
        bufferedJumpUsable = false;
        coyoteUsable = false;
        
        // perform actual jump
        anim->SetCurrentAnim(canDoubleJump ? DOUBLEJUMP : JUMP);
        canDoubleJump = !canDoubleJump;
        velocityAccumulator.y = canDoubleJump ? stats->GetJumpForce() : stats->GetDoubleJumpForce();
    }

    jumpToConsume = false;
}

#pragma endregion


void Player::CalculateDirectionalMovement(float dt)
{
    // TODO: Fix jittre
    if (horizontalInput == 0.f)
    {
        // Get the appropriate deceleration factor
        const auto decel = grounded ? stats->GetGroundFriction() : stats->GetAirFriction();
        // Add to the velocity by a fixed amount depending on the step size (decel * dt)
        if (abs(0 - velocityAccumulator.x) <= decel * dt)
            velocityAccumulator.x = 0;
        else
            velocityAccumulator.x += sgn(0 - velocityAccumulator.x) * (decel * dt);
    }
    else
    {
        if (abs((horizontalInput * maxSpeedX) - velocityAccumulator.x) <= stats->GetAcceleration() * dt)
            velocityAccumulator.x = (horizontalInput * maxSpeedX);
        else
            velocityAccumulator.x += sgn((horizontalInput * maxSpeedX) - velocityAccumulator.x) * (stats->GetAcceleration() * dt);
    }
}

void Player::ApplyMovement()
{
    velocity = velocityAccumulator;
    MoveX(velocity.x);
    MoveY(velocity.y);
}
