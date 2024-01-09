#pragma once

#include <SDL_rect.h>
#include "template.h"

struct BoxCollider
{
public:
    BoxCollider() = default;
    BoxCollider(const Tmpl8::vec2 position, const Tmpl8::vec2 size) {
        hitBox.x = static_cast<int>(position.x);
        hitBox.y = static_cast<int>(position.y);
        hitBox.w = static_cast<int>(size.x);
        hitBox.h = static_cast<int>(size.y);
    }
    ~BoxCollider() = default; 
    
    void SetPosition(const Tmpl8::vec2 position) {
        hitBox.x = static_cast<int>(position.x);
        hitBox.y = static_cast<int>(position.y);
    }
    
    SDL_Rect GetHitBox() const { return hitBox; }

private:
    // Why make a whole new rectangle class and collision when SDL supports it out of the box? :)
    SDL_Rect hitBox;
};
