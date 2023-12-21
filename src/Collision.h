#pragma once
#include "SDL_rect.h"
#include "template.h"

namespace Tmpl8
{
    
class Collision
{
public:
    static bool RectIntersect(const SDL_Rect* a, const SDL_Rect* b, vec2& normal);
    static bool RectIntersectAt(const SDL_Rect* a, vec2 aOffset, vec2& normal, class World* world);
};
    
}

