#include "Solid.h"

#include <vector>

Solid::Solid(vec2 position, vec2 size) : position(position), hitBox(new BoxCollider(position, size))
{
}


