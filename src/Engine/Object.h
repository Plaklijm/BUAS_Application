#pragma once
#include "Actor.h"

namespace Tmpl8
{
    class Sprite;
}

enum Type
{
    PLAYERSTART = 0,
    PLAYEREND,
    COLLECTABLE,
    PUSHABLE
};

class Object : public Actor
{
public:
    Object(Tmpl8::vec2 position, Tmpl8::vec2 size, class World* world, Type type);
    
    void Update(float dt) {}
    void UpdatePhysics(float dt) {}
    
    void Render(Tmpl8::Surface* screen) const;

    void Collect() const;
    
    Type GetType() const { return type; }

    void SetSprite(Tmpl8::Sprite* sprite);
private:
    Tmpl8::Sprite* sprite;
    Type type;
};  
