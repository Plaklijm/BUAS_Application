#include "Button.h"

#include "../surface.h"
#include "../template.h"

Button::Button(Tmpl8::Sprite* buttonSprite, Tmpl8::vec2 position) : button(SDL_Rect()),
    buttonSprite(buttonSprite)
{
    button.x = position.x;
    button.y = position.y;
    button.w = buttonSprite->GetWidth();
    button.h = buttonSprite->GetHeight();
}

bool Button::IsHovered(SDL_Point point)
{
    // TODO: Add functionality for hovering like sound and opacity change
    if (SDL_PointInRect(&point, &button))
    {
        //buttonSprite->SetFrame(1);
        return true;
    }
    
    //buttonSprite->SetFrame(0);
    return false;
}

void Button::OnPressed(const std::function<void()>& function)
{
    // Execute the other stuff first
    //buttonSprite->SetFrame(1);

    // Maybe a timer to wait until the sound has finished;
    function();
}

void Button::DisplayButton(Tmpl8::Surface* screen) const
{
    buttonSprite->Draw(screen, button.x, button.y);
    //screen->Print("PLAY", button.x, button.y, 500);
    screen->Box(button.x, button.y, button.x + button.w, button.y + button.h, 0xffffff);
}
