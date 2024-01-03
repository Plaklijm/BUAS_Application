#pragma once
#include <SDL2-2.28.5/include/SDL_Rect.h>
#include "template.h"

class Object;

class Collision
{
public:
    static bool RectIntersect(const SDL_Rect* a, const SDL_Rect* b, Tmpl8::vec2& normal);
    static bool RectIntersectAt(const SDL_Rect* a, Tmpl8::vec2 aOffset, Tmpl8::vec2& normal, const class World* world);
    static Object* RectIntersectObjects(const SDL_Rect* a, const class World* world);
};

