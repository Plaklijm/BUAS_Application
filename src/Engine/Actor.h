#pragma once
#include "template.h"
#include "BoxCollider.h"
#include "../Map/World.h"

class Solid;

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

    Actor(Tmpl8::vec2 position, Tmpl8::vec2 size, class World* world);

    Tmpl8::vec2 GetPosition() const             { return position; }
    BoxCollider* GetCollider() const            { return hitBox; }
    Tmpl8::vec2 GetCollisionNormalX() const     { return collisionNormalX; }
    Tmpl8::vec2 GetCollisionNormalY() const     { return collisionNormalY; }

private:
    void OnCollideX();
    void OnCollideY();
        
    float xRemainder{};
    float yRemainder{};
    
    Tmpl8::vec2 position = Tmpl8::vec2::Zero();
    Tmpl8::vec2 collisionNormalX = Tmpl8::vec2::Zero();
    Tmpl8::vec2 collisionNormalY = Tmpl8::vec2::Zero();
    
    BoxCollider* hitBox;
};


