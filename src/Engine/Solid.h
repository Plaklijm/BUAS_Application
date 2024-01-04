#pragma once
#include "template.h"
#include "BoxCollider.h"

using namespace Tmpl8;

class Solid
{
public:
    Solid(vec2 position, vec2 size);

    vec2 GetPosition() const { return position; }
    BoxCollider* GetCollider() const { return hitBox; }

private:
    vec2 position = vec2::Zero();
    BoxCollider* hitBox;
};
