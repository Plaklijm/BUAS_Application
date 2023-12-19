#pragma once

#include <SDL_rect.h>

using namespace Tmpl8;

struct BoxCollider
{
public:
    BoxCollider() = default;
    BoxCollider(const int x, const int y, const int w, const int h) {
        hitBox.x = x;
        hitBox.y = y;
        hitBox.w = w;
        hitBox.h = h;
    }
    
    ~BoxCollider();

    // TODO: Update the position of the collider
    void SetPosition() {}
private:
    // Why make a whole new rectangle class and collision when SDL supports it out of the box? :)
    SDL_Rect hitBox;
};
