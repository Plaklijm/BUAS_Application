#pragma once
#include "template.h"
#include "BoxCollider.h"

// Very small class that handles the static objects in the scene like the world
// This could also be used for moving platforms etc -> See actor.h for more references
class Solid
{
public:
    Solid(Tmpl8::vec2 position, Tmpl8::vec2 size);

    Tmpl8::vec2 GetPosition() const { return position; }
    BoxCollider* GetCollider() const { return hitBox; }

private:
    Tmpl8::vec2 position = Tmpl8::vec2::Zero();
    BoxCollider* hitBox;
};
