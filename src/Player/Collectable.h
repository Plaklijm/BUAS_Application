#pragma once
#include "../Engine/Actor.h"

class Collectable : public Actor
{
public:
    Collectable(vec2 position, vec2 size, World* world);
    
    void Update(float dt);
    
    void UpdatePhysics(float dt);
    void Render(Surface* screen);

    void Collect();
private:
    
};
