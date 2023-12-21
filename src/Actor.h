#pragma once
#include "template.h"

using namespace Tmpl8;
struct BoxCollider;

/**
 * \brief This class is based on the implementation seen in Celeste
 * Following this article of the celeste Dev: https://www.mattmakesgames.com/articles/celeste_and_towerfall_physics/index.html
 * Some elements are directly copied like the way movement is handled in the MoveX and MoveY functions
 * This was also a handy guideline because the plan from the beginning was to make something inspired by the celeste Movement
 */
namespace Tmpl8
{
class Actor
{
protected:
    void MoveX(float amount);
    void MoveY(float amount);

    Actor(vec2 position, vec2 size, class World* world);

    World* world;
public:
    vec2 GetPosition() const { return position; }
    BoxCollider* GetCollider() const { return hitBox; }
    vec2 GetCollisionNormal() const { return collisionNormal; }
private:
    void OnCollideX();
    void OnCollideY();
    
    float xRemainder{};
    float yRemainder{};
    
    vec2 position = vec2::Zero();
    vec2 collisionNormal = vec2::Zero();
    BoxCollider* hitBox;
};
    
}
