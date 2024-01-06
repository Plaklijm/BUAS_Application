#pragma once
#include <functional>
#include <SDL_rect.h>

namespace Tmpl8
{
    class Sprite;
    class Surface;
    class vec2;
}

class Button
{
public:
    Button(Tmpl8::Sprite* buttonSprite, Tmpl8::vec2 position);
    
    bool IsHovered(SDL_Point point);
    void OnPressed(const std::function<void()>& function);

    void DisplayButton(Tmpl8::Surface* screen) const;
private:
    SDL_Rect button;
    Tmpl8::Sprite* buttonSprite;
    bool playOneShot = true;
};
