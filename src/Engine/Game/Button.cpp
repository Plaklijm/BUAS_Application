#include "Button.h"

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


bool Button::IsHovered(SDL_Point point)
{
    if (SDL_PointInRect(&point, &button))
    {
        if (playOneShot)
        {
            // Do once, so set the next frame and play a sound
            buttonSprite->SetFrame(1);
            SoundManager::Instance()->PlaySound(s_CLICK);
            playOneShot = false;
        }
        return true;
    }

    // this will only happen if the button isnt hovered
    buttonSprite->SetFrame(0);
    playOneShot = true;
    return false;
}

void Button::OnPressed(const std::function<void()>& function)
{
    // Play a click sound
    SoundManager::Instance()->PlaySound(s_CLICK);

    // Execute the function that is given
    // this way the actual implementation is abstract and can be anything we want it to be
    function();
}

// render the button on the screen
void Button::DisplayButton(Tmpl8::Surface* screen) const
{
    buttonSprite->Draw(screen, button.x, button.y);
}
