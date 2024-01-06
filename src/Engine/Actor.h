#pragma once
#include "template.h"
#include "BoxCollider.h"
#include "../Map/World.h"
#include "Collision.h"

class Solid;
using namespace Tmpl8;

/**
 * \brief This class is based on the implementation seen in Celeste
 * Following this article of the celeste Dev: https://www.mattmakesgames.com/articles/celeste_and_towerfall_physics/index.html
 * Some elements are directly copied like the way movement is handled in the MoveX and MoveY functions
 * This was also a handy guideline because the plan from the beginning was to make something inspired by the celeste Movement
 */
class Actor
{
protected:
    
    class World* world;
public:
    void MoveX(float amount, bool ignoreObjects = false, const Actor* playerRef = nullptr);
    void MoveY(float amount);

    Actor(vec2 position, vec2 size, class World* world);

    vec2 GetPosition() const            { return position; }
    BoxCollider* GetCollider() const    { return hitBox; }
    vec2 GetCollisionNormalX() const    { return collisionNormalX; }
    vec2 GetCollisionNormalY() const    { return collisionNormalY; }

private:
    void OnCollideX();
    void OnCollideY();
        
    float xRemainder{};
    float yRemainder{};
    
    vec2 position = vec2::Zero();
    vec2 collisionNormalX = vec2::Zero();
    vec2 collisionNormalY = vec2::Zero();
    
    BoxCollider* hitBox;
};


