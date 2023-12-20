#pragma once


#include "Actor.h"
#include "surface.h"
#include "template.h"

namespace Tmpl8
{
    class InputManager;
}

class AABB;

using namespace Tmpl8;

/*enum anims
{
    A_Idle,
    A_Walk,
    A_Jump
};*/


constexpr float gravity {.0001};

class Player : Actor
{
private:
    // LOOK FOR A PLACE TO PUT THESE
    /*unsigned int frame = 0;
    float animationTime{};
    float animationSpeed = .1f;*/
private:
    InputManager*               pInput;
    Sprite*                     sprite;

    struct PlayerStats*         stats;
    class BoxCollider*          collider;
    class TestCollision*        testCollision;
    
    vec2                        position;
    vec2                        velocity;
    vec2                        friction;
    vec2                        gravity;
    vec2                        force;

    bool                        flipHorizontally;
    
    // Input variables
    float                       horizontalInput{};
    bool                        jumpDown{};
    bool                        jumpHeld{};
    bool                        sprintPressed{};
    bool                        crouchPressed{};
    bool                        left{};
    bool                        right{};

    //bool isFacingRight;
public:
    Player(InputManager* input);
    ~Player();

    void Update(float dt);
    
    void ApplyForce(vec2 inputForce);
    void ApplyGravity();
    void ApplyFriction(vec2 friction);
    void ClearForces();

    void Move(float dt);
    void LimitVelocity();

    void UpdatePhysics(float dt);
    void RenderPlayer(Surface* screen);
    //void HandleAction(ActionType action);

    //void SwitchAnim(anims animToPlay);
    
private:
    //void FlipSprite();
    //void UpdateAnim(float dt);
    
};
