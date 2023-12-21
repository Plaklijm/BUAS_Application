#pragma once
#include "template.h"

using namespace Tmpl8;
struct BoxCollider;

class Solid
{
protected:
    void Move(vec2 amount);

public:
    Solid(vec2 position, vec2 size);
    
    vec2 GetPosition() const { return position; }
    BoxCollider* GetCollider() const { return hitBox; }

private:
    float xRemainder{};
    float yRemainder{};
    
    vec2 position = vec2::Zero();
    BoxCollider* hitBox;
};
