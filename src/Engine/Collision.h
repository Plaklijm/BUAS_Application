#pragma once
#include "../Engine/BoxCollider.h"
#include "template.h"

class Object;

class Collision
{
public:
    static bool RectIntersect(const SDL_Rect* a, const SDL_Rect* b, vec2& normal);
    static bool RectIntersectAt(const SDL_Rect* a, vec2 aOffset, vec2& normal, const class World* world);
    static bool RectIntersectAt(const SDL_Rect* a, vec2 aOffset, vec2& normal, const class World* world, bool& isPushing, Object*& pushAbleObject);
    static Object* RectIntersectObjects(const SDL_Rect* a, const class World* world);
};

