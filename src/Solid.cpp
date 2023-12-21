#include "Solid.h"

#include "BoxCollider.h"

Solid::Solid(vec2 position, vec2 size) : position(position), hitBox(new BoxCollider(position, size))
{
}

void Solid::Move(vec2 amount)
{
    // add movement function for the solids (can make moving platforms with this)
}

