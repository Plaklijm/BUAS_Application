﻿#include "Button.h"

#include "../surface.h"
#include "../template.h"
#include "../SoundManager.h"

Button::Button(Tmpl8::Sprite* buttonSprite, Tmpl8::vec2 position) : button(SDL_Rect()),
    buttonSprite(buttonSprite)
{
    button.x = position.x;
    button.y = position.y;
    button.w = buttonSprite->GetWidth();
    button.h = buttonSprite->GetHeight();
}

bool Button::IsHovered(SDL_Point point) const
{
    if (SDL_PointInRect(&point, &button))
        return true;

    return false;
}

void Button::OnPressed(const std::function<void()>& function)
{
    SoundManager::Instance()->PlaySound(s_CLICK);

    function();
}

void Button::DisplayButton(Tmpl8::Surface* screen) const
{
    buttonSprite->Draw(screen, button.x, button.y);
}
