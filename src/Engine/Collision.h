#pragma once
#include "template.h"
#include "../Engine/BoxCollider.h"

class Object;

class Collision
{
public:
    static bool RectIntersect(const SDL_Rect* a, const SDL_Rect* b, Tmpl8::vec2& normal);
    static bool RectIntersectAt(const SDL_Rect* a, Tmpl8::vec2 offset, const SDL_Rect* b, Tmpl8::vec2& normal);
    static bool RectIntersectAt(const SDL_Rect* a, Tmpl8::vec2 offset, Tmpl8::vec2& normal, const class World* world);
    
    static Object* RectIntersectObjects(const SDL_Rect* a, const class World* world);
    static Object* RectIntersectObjects(const SDL_Rect* a, Tmpl8::vec2 offset, Tmpl8::vec2& normal, const class World* world);

private:
    static Tmpl8::vec2 CalculateNormal(const SDL_Rect* rect, SDL_Rect result);
};

