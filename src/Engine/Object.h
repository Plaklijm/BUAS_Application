#pragma once
#include "../src/Engine/Actor.h"

namespace Tmpl8
{
    class Sprite;
}

enum Type
{
    PLAYERSTART = 0,
    PLAYEREND,
    COLLECTABLE,
};

class Object : public Actor
{
public:
    Object(vec2 position, vec2 size, World* world, Type type);
    
    void Update(float dt);
    
    void UpdatePhysics(float dt);
    void Render(Surface* screen) const;

    void Collect() const;
    
    Type GetType() const { return type; }

    void SetSprite(Sprite* sprite);
private:
    Sprite* sprite;
    Type type;
};  
