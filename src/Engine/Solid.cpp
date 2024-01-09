#include "Solid.h"

#include <vector>

Solid::Solid(Tmpl8::vec2 position, Tmpl8::vec2 size) : position(position), hitBox(new BoxCollider(position, size))
{
}


