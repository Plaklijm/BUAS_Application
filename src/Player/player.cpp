#include "player.h"

#include <algorithm>

#include "../Animation/AnimationSystem.h"
#include "../Engine/BoxCollider.h"
#include "../Engine/InputManager.h"
#include "PlayerStats.h"
#include "../Map/GameMap.h"
#include "../Engine/Object.h"
#include "../Engine/SoundManager.h"

// https://www.myphysicslab.com/engine2D/rigid-body-en.html
SDL_Rect pushCol;
Player::Player(vec2 startPos, InputManager* input, World* world) : Actor(startPos, vec2(28,40), world)
{
    stats = new PlayerStats();

    pInput = input;

    // Initialize Animation
    anim = new AnimationSystem();
    anim->AddAnim(a_IDLE, std::make_unique<Animation>(new Sprite(new Surface("assets/player/Sprites/p_Idle.png"), 10), stats->GetAnimRate()));
    anim->AddAnim(a_WALK, std::make_unique<Animation>(new Sprite(new Surface("assets/player/sprites/p_Walk.png"), 8), stats->GetAnimRate()));
    anim->AddAnim(a_RUN, std::make_unique<Animation>(new Sprite(new Surface("assets/player/sprites/p_Run.png"), 8), stats->GetAnimRate()));
    anim->AddAnim(a_JUMP, std::make_unique<Animation>(new Sprite(new Surface("assets/player/sprites/p_Jump.png"), 3), stats->GetAnimRate(), false));
    anim->AddAnim(a_DOUBLEJUMP, std::make_unique<Animation>(new Sprite(new Surface("assets/player/sprites/p_DoubleJump.png"), 6), stats->GetAnimRate() * .65f, false));
    anim->AddAnim(a_COLLECT, std::make_unique<Animation>(new Sprite(new Surface("assets/player/sprites/p_Pickup.png"), 4), stats->GetAnimRate(), false));
    anim->AddAnim(a_PUSH, std::make_unique<Animation>(new Sprite(new Surface("assets/player/sprites/p_Push.png"), 10), stats->GetAnimRate()));
    anim->AddAnim(a_PULL, std::make_unique<Animation>(new Sprite(new Surface("assets/player/sprites/p_Pull.png"), 6), stats->GetAnimRate()));
    
    currentAnimState = a_IDLE;
    anim->SetCurrentAnim(currentAnimState);

    // Initialize variables    
    velocityAccumulator = {0, 0};
    canDoubleJump = true;
    flipHorizontally = false;
    isJumping = 0;
    collect = false;
    stepTimer.reset();
    stepInterval = 400.f;
    pushCol.w = 48;
    pushCol.h = 20;
    isPushingObj = false;
    isPullingObj = false;
}

Player::~Player()
{
    
}

float time;
float frameLeftGrounded = std::numeric_limits<float>::lowest();

int currentFrame;
int currentAnimFrameCount;

bool dead = false;
float collectTimer = .3f;
void Player::Update(float dt)
{
    // TODO: Fix this update method PLS :D
    time += dt;

    // Handle input
    const auto left = pInput->KeyPressed(SDL_SCANCODE_A);
    const auto right = pInput->KeyPressed(SDL_SCANCODE_D);
    // Set the horizontal input to -1 if left 1 if right and 0 if both left and right are pressed
    horizontalInput = right - left;
    
    // TODO: Fix controller input and add Axis support for left right and crouch
    jumpDown = pInput->KeyDown(SDL_SCANCODE_SPACE);
    jumpHeld = pInput->KeyPressed(SDL_SCANCODE_SPACE);

    sprintPressed = pInput->KeyPressed(SDL_SCANCODE_LSHIFT);

    moveObjectPressed = pInput->KeyPressed(SDL_SCANCODE_E);
    
    if (sprintPressed || isPushingObj || isPullingObj)
        maxSpeedX = stats->GetWalkSpeed();
    else
        maxSpeedX = stats->GetSprintSpeed();
    
    if (jumpDown)
    {
        jumpToConsume = true;
        timeJumpWasPressed = time;
    }

    if (GetCollisionNormalY().y > 0)
    {   
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
    }
    else
    {
        grounded = false;
        frameLeftGrounded = time;
    }

    if (collect)
    {
        collectTimer -= dt;
        if (collectTimer < 0)
        {
            collectTimer = .3f;
            collect = false;
        }
    }
    
    if (grounded)
    {
        if (stepTimer.elapsed() > stepInterval && abs(horizontalInput) > 0)
        {
            stepTimer.reset();
            SoundManager::Instance()->PlaySound(s_WALK);
        }  
    }
    

    
    anim->Update();
}

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
    if (horizontalInput < 0 && (!isPushingObj || !isPullingObj))
        flipHorizontally = true;
    if (horizontalInput > 0 && (!isPushingObj || !isPullingObj))
        flipHorizontally = false;
    
    // Set the correct animation according to the current state of the game
    if (isJumping > 0)
    {
        if (isJumping == 1)
            currentAnimState = a_JUMP;
        else
            currentAnimState = a_DOUBLEJUMP;
    }
    else
    {
        // Make sure the correct animation is played, so when we walk against a wall it will be idle etc
        // Because the wall hit etc is already calculated here I also use it to stop the player from playing any stepsounds
        if (velocity.x != 0)
        {
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
    }

    if (collect)
    {
        currentAnimState = a_COLLECT;
    }

    if (isPushingObj)
    {
        currentAnimState = a_PUSH;
    }
    else if (isPullingObj)
    {
        currentAnimState = a_PULL;
    }
    
    anim->SetCurrentAnim(currentAnimState);
}


void Player::HandlePushObj()
{
    // TODO CLEANUP FUNCTION
    vec2 normal;
    // using the offset to prevent the player from getting stuck (the offset rect gets calculated again in the other func tho)
    const auto pushAbleObject = Collision::RectIntersectObjects(&pushCol, vec2(0,0), normal, world);
    if (pushAbleObject != nullptr && pushAbleObject->GetType() == PUSHABLE)
    {
        if (moveObjectPressed && abs(horizontalInput) > 0)
        {
            printf("%f\n", normal.x);
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

            pushAbleObject->MoveX(velocity.x, true);
            return;
        }
    }
    
    isPushingObj = false;
    isPullingObj = false;
}

void Player::RenderPlayer(Surface* screen)
{
    const auto b1 = GetCollider()->GetHitBox();
    screen->Box(b1.x, b1.y, b1.x + b1.w, b1.y + b1.h, 0xffffff);

    const auto b2 = pushCol;
    screen->Box(b2.x, b2.y, b2.x + b2.w, b2.y + b2.h, 0xffffff);
    
    anim->Render(screen, GetPosition().x - stats->GetSpriteOffset(), GetPosition().y, flipHorizontally);
}

void Player::Collect()
{
    SoundManager::Instance()->PlaySound(s_COLLECT);
    collect = true;
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
        SoundManager::Instance()->PlaySound(canDoubleJump? s_DOUBLEJUMP : s_JUMP);
        isJumping = canDoubleJump ? 2 : 1;
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
    MoveX(velocity.x, false);
    MoveY(velocity.y);
    pushCol.x = GetPosition().x - stats->GetSpriteOffset();
    pushCol.y = GetPosition().y + stats->GetSpriteOffset();
}
