#include "player.h"

#include <algorithm>

#include "../Animation/AnimationSystem.h"
#include "../Engine/InputManager.h"
#include "PlayerStats.h"
#include "../Engine/Object.h"
#include "../Engine/SoundManager.h"
#include "Engine/Collision.h"

// Player class, handles movement calculations etc
// Would've been a bit neater if put into a statemachine, but seeing how this class evolved over time it isn't/wasn't really
// ideal, so in the end I decided to stick with this approach, although it got a bit messy the more functionality got added


Player::Player(Tmpl8::vec2 startPos, InputManager* input, World* world) :
    Actor(startPos, Tmpl8::vec2(28,40), world)
{
    stats = new PlayerStats();

    pInput = input;

    // Initialize Animation
    // (I know these are a bit too long to be on a single line, but there is so much going on, its more readable this way)
    anim = new AnimationSystem();
    anim->AddAnim(a_IDLE, std::make_unique<Animation>(new Tmpl8::Sprite(new Tmpl8::Surface("assets/player/Sprites/p_Idle.png"), 10), stats->GetAnimRate()));
    anim->AddAnim(a_WALK, std::make_unique<Animation>(new Tmpl8::Sprite(new Tmpl8::Surface("assets/player/sprites/p_Walk.png"), 8), stats->GetAnimRate()));
    anim->AddAnim(a_RUN, std::make_unique<Animation>(new Tmpl8::Sprite(new Tmpl8::Surface("assets/player/sprites/p_Run.png"), 8), stats->GetAnimRate()));
    anim->AddAnim(a_JUMP, std::make_unique<Animation>(new Tmpl8::Sprite(new Tmpl8::Surface("assets/player/sprites/p_Jump.png"), 3), stats->GetAnimRate(), false));
    anim->AddAnim(a_DOUBLEJUMP, std::make_unique<Animation>(new Tmpl8::Sprite(new Tmpl8::Surface("assets/player/sprites/p_DoubleJump.png"), 6), stats->GetAnimRate() * .65f, false));
    anim->AddAnim(a_COLLECT, std::make_unique<Animation>(new Tmpl8::Sprite(new Tmpl8::Surface("assets/player/sprites/p_Pickup.png"), 4), stats->GetAnimRate(), false));
    anim->AddAnim(a_PUSH, std::make_unique<Animation>(new Tmpl8::Sprite(new Tmpl8::Surface("assets/player/sprites/p_Push.png"), 10), stats->GetAnimRate()));
    anim->AddAnim(a_PULL, std::make_unique<Animation>(new Tmpl8::Sprite(new Tmpl8::Surface("assets/player/sprites/p_Pull.png"), 6), stats->GetAnimRate() * 1.25f));
    anim->AddAnim(a_LAND, std::make_unique<Animation>(new Tmpl8::Sprite(new Tmpl8::Surface("assets/player/sprites/p_Land.png"), 4), stats->GetAnimRate() * .5f, false));
    
    currentAnimState = a_IDLE;
    anim->SetCurrentAnim(currentAnimState);

    // Initialize variables    
    velocityAccumulator = {0, 0};
    canDoubleJump = true;
    flipHorizontally = false;
    collect = false;
    stepTimer.reset();
    stepInterval = 400.f;
    isPushingObj = false;
    isPullingObj = false;
    maxSpeedX = stats->GetWalkSpeed();

    pushCol.w = 42;
    pushCol.h = 20;
}

float time;
float frameLeftGrounded = std::numeric_limits<float>::lowest();

void Player::Update(float dt)
{
    time += dt;

    HandleInput();
    SetMaxSpeed();
    SetGrounded();
}

#pragma region Update
void Player::SetMaxSpeed()
{
    if (isPushingObj || isPullingObj)
        maxSpeedX = stats->GetPushPullSpeed();
    else if (sprintPressed)
        maxSpeedX = stats->GetWalkSpeed();
    else
        maxSpeedX = stats->GetSprintSpeed();
}

void Player::SetGrounded()
{
    if (GetCollisionNormalY().y > 0)
    {
        if (velocity.y > 15.5f || isJumping)
            landed = true;
        
        grounded = true;
        coyoteUsable = true;
        bufferedJumpUsable = true;
        endedJumpEarly = false;
        canDoubleJump = false;
        isJumping = false;
    }
    else if (GetCollisionNormalY().y < 0)
    {
        // If you hit an ceiling zero out the velocity
        velocityAccumulator.y = 0;
        grounded = false;
        landed = false;
        landed = false;
    }
    else
    {
        landed = false;
        grounded = false;
        frameLeftGrounded = time;
    }

    // Just some sound stuff when you are grounded to simulate footsteps (doesn't sound good lol but it's something)
    if (grounded)
    {
        if (stepTimer.elapsed() > stepInterval && abs(horizontalInput) > 0)
        {
            stepTimer.reset();
            SoundManager::Instance()->PlaySound(s_WALK);
        }  
    }
}

void Player::HandleInput()
{
    const auto left = pInput->KeyPressed(SDL_SCANCODE_A);
    const auto right = pInput->KeyPressed(SDL_SCANCODE_D);
    // Set the horizontal input to -1 if left 1 if right and 0 if both left and right are pressed
    horizontalInput = right - left;
    
    jumpDown = pInput->KeyDown(SDL_SCANCODE_SPACE);
    jumpHeld = pInput->KeyPressed(SDL_SCANCODE_SPACE);

    sprintPressed = pInput->KeyPressed(SDL_SCANCODE_LSHIFT);

    moveObjectPressed = pInput->KeyPressed(SDL_SCANCODE_W);
    
    if (jumpDown)
    {
        jumpToConsume = true;
        timeJumpWasPressed = time;
    }
}
#pragma endregion

void Player::UpdatePhysics(float dt)
{
    HandleAnimations();
    CalculateGravity(dt);
    HandleJump();
    CalculateDirectionalMovement(dt);
    HandlePushObj();
    ApplyMovement();
}

void Player::HandleAnimations()
{
    // Very bulky but it needs to be like this, A better way to handle this mess would've been a state machine but yeah
    // that in turn would also make a lot of mess, and to convert everything to a statemachine now would be a nightmare
    
    if (horizontalInput < 0 && (!isPushingObj || !isPullingObj))
        flipHorizontally = true;
    if (horizontalInput > 0 && (!isPushingObj || !isPullingObj))
        flipHorizontally = false;
    
    // Set the correct animation according to the current state of the game
    if (isJumping > 0)
            currentAnimState = isJumping == 1 ? a_JUMP : a_DOUBLEJUMP;
    else if (velocity.x != 0)
    {
        // Make sure the correct animation is played, so when we walk against a wall it will be idle etc
        // Because the wall hit etc is already calculated here I also use it to stop the player from playing any stepsounds
        if (abs(GetCollisionNormalX().x) == 0)
        {
            if (abs(GetCollisionNormalX().y) == 0)
                currentAnimState = sprintPressed ? a_WALK : a_RUN;
            else
            {
                currentAnimState = a_IDLE;
                stepTimer.reset();
            }
        }
        else
        {
            currentAnimState = a_IDLE;
            stepTimer.reset();
        }
    }
    else
        currentAnimState = a_IDLE;

    // Just some overriding stuff with higher priority than the prev anims
    if (collect)
        currentAnimState = a_COLLECT;
    else if (isPushingObj)
        currentAnimState = a_PUSH;
    else if (isPullingObj)
        currentAnimState = a_PULL;
    else if (landed)
        currentAnimState = a_LAND;

    
    anim->SetCurrentAnim(currentAnimState);
    anim->Update();

    // Some resetting of variables
    if (anim->IsAnimFinished(a_LAND))
        landed = false;
    if (anim->IsAnimFinished(a_COLLECT))
        collect = false;
}

void Player::HandlePushObj()
{
    Tmpl8::vec2 normal;
    // using the offset to prevent the player from getting stuck (the offset rect gets calculated again in the other func tho)
    const auto pushAbleObject = Collision::RectIntersectObjects(&pushCol, Tmpl8::vec2(0,0), normal, world);
    if (pushAbleObject != nullptr && pushAbleObject->GetType() == PUSHABLE)
    {
        // Check in a scuffed way if the player is pushing or pulling an object based on input and normal hit
        if (moveObjectPressed && abs(horizontalInput) > 0)
        {
            if (normal.x > 0)
            {
                if (horizontalInput < 0)
                {
                    isPushingObj = true;
                    isPullingObj = false;
                }
                else if (horizontalInput > 0)
                {
                    isPullingObj = true;
                    isPushingObj = false;
                }
                flipHorizontally = true;
            }
            if (normal.x < 0)
            {
                if (horizontalInput < 0)
                {
                    isPullingObj = true;
                    isPushingObj = false;
                }
                else if (horizontalInput > 0)
                {
                    isPushingObj = true;
                    isPullingObj = false;
                }
                flipHorizontally = false;
            }
            // Move the object
            pushAbleObject->MoveX(velocity.x, true, this);
            return;
        }
    }
    
    isPushingObj = false;
    isPullingObj = false;
}

void Player::RenderPlayer(Tmpl8::Surface* screen) const
{
    anim->Render(screen, GetPosition().x - stats->GetSpriteOffset(), GetPosition().y, flipHorizontally);
}

void Player::Collect()
{
    SoundManager::Instance()->PlaySound(s_COLLECT);
    collect = true;
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
        SoundManager::Instance()->PlaySound(canDoubleJump? s_DOUBLEJUMP : s_JUMP);
        isJumping = canDoubleJump ? 2 : 1;
        canDoubleJump = !canDoubleJump;
        velocityAccumulator.y = canDoubleJump ? stats->GetJumpForce() : stats->GetDoubleJumpForce();
    }

    jumpToConsume = false;
}

#pragma endregion

#pragma region Movement
void Player::CalculateGravity(float dt)
{
    if (grounded)
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
            velocityAccumulator.y += Tmpl8::sgn(stats->GetMaxFallSpeed() - velocityAccumulator.y) * (inAirGravity * dt);
    }
}

void Player::CalculateDirectionalMovement(float dt)
{
    if (horizontalInput == 0.f)
    {
        // Get the appropriate deceleration factor
        const auto decel = grounded ? stats->GetGroundFriction() : stats->GetAirFriction();
        // Add to the velocity by a fixed amount depending on the step size (decel * dt)
        if (abs(0 - velocityAccumulator.x) <= decel * dt)
            velocityAccumulator.x = 0;
        else
            velocityAccumulator.x += Tmpl8::sgn(0 - velocityAccumulator.x) * (decel * dt);
    }
    else
    {
        if (abs((horizontalInput * maxSpeedX) - velocityAccumulator.x) <= stats->GetAcceleration() * dt)
            velocityAccumulator.x = (horizontalInput * maxSpeedX);
        else
            velocityAccumulator.x += Tmpl8::sgn((horizontalInput * maxSpeedX) - velocityAccumulator.x) * (stats->GetAcceleration() * dt);
    }
}

void Player::ApplyMovement()
{
    velocity = velocityAccumulator;
    MoveX(velocity.x);
    MoveY(velocity.y);
    // Just some code to make the collider for chekcing the pushable objects move w the player
    pushCol.x = GetPosition().x - 2 - stats->GetSpriteOffset()/2;
    pushCol.y = GetPosition().y + stats->GetSpriteOffset();
}
#pragma endregion
