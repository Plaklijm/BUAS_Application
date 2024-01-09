#include "InputManager.h"

#include <cstring>
#include <SDL_mouse.h>
#include <SDL2-2.28.5/include/SDL_keyboard.h>

InputManager* InputManager::instance = nullptr;

InputManager* InputManager::Instance()
{
    if (!instance)
        instance = new InputManager();

    return instance;
}

void InputManager::Release()
{
    delete instance;
    instance = nullptr;
}

void InputManager::SetWindowParams(bool fullscreen, float windowX, float windowY)
{
    // Sets the window parameters based on the resolution of the screen, (needs to be done in order to correctly handle mouse pos)
    this->fullscreen = fullscreen;
    this->windowX = windowX;
    this->windowY = windowY;
}

InputManager::InputManager()
{
    keyboardState = SDL_GetKeyboardState(&keyLength);
    prevKeyboardState = new Uint8[keyLength];
    memcpy(prevKeyboardState, keyboardState, keyLength);
}

InputManager::~InputManager()
{
    delete[] prevKeyboardState;
    prevKeyboardState = nullptr;
}

// -----------------------------------------------------------
// Keyboard Events
// -----------------------------------------------------------

// You are implemented key functions >:(
bool InputManager::KeyDown(SDL_Scancode scanCode) const
{
    return !prevKeyboardState[scanCode] && keyboardState[scanCode];
}
    
bool InputManager::KeyPressed(SDL_Scancode scanCode) const
{
    return keyboardState[scanCode];
}
    
bool InputManager::KeyReleased(SDL_Scancode scanCode) const
{
    return prevKeyboardState[scanCode] && !keyboardState[scanCode];
}

bool InputManager::MouseButtonDown(MOUSE_BUTTONS button) const
{
    Uint32 mask = 0;

    switch (button) {
    case LEFT:
        mask = SDL_BUTTON_LMASK;
        break;
    case RIGHT:
        mask = SDL_BUTTON_RMASK;
        break;
    case MIDDLE:
        mask = SDL_BUTTON_MMASK;
        break;
    }

    return !(prevMouseState & mask) && (mouseState & mask);
}

bool InputManager::MouseButtonPressed(MOUSE_BUTTONS button) const
{
    Uint32 mask = 0;

    switch (button) {
    case LEFT:
        mask = SDL_BUTTON_LMASK;
        break;
    case RIGHT:
        mask = SDL_BUTTON_RMASK;
        break;
    case MIDDLE:
        mask = SDL_BUTTON_MMASK;
        break;
    }

    return (mouseState & mask);
}

bool InputManager::MouseButtonReleased(MOUSE_BUTTONS button) const
{
    Uint32 mask = 0;

    switch (button) {
    case LEFT:
        mask = SDL_BUTTON_LMASK;
        break;
    case RIGHT:
        mask = SDL_BUTTON_RMASK;
        break;
    case MIDDLE:
        mask = SDL_BUTTON_MMASK;
        break;
    }

    return (prevMouseState & mask) && !(mouseState & mask);
}

Tmpl8::vec2 InputManager::MousePos() const
{
    return actualMousePos;
}

void InputManager::Update()
{
    // A check if we are full screen, Scale the mouse position to that screen,
    // so even if you are at 1080p, the mouse position will be given in the resolution of the context window
    // So in this case the ScreenWidth and ScreenHeight variables set in the template.h
    if (fullscreen)
    {
        mouseState = SDL_GetMouseState(&mouseXPos, &mouseYPos);
        const auto tempW = static_cast<float>(mouseXPos) * (static_cast<float>(ScreenWidth) / windowX);
        const auto tempH = static_cast<float>(mouseYPos) * (static_cast<float>(ScreenHeight) / windowY);
        actualMousePos.x = round(tempW);
        actualMousePos.y = round(tempH);
    }
    else
    {
        mouseState = SDL_GetMouseState(&mouseXPos, &mouseYPos);
        actualMousePos = {static_cast<float>(mouseXPos), static_cast<float>(mouseYPos)};
    }
}

void InputManager::UpdatePrevInput()
{
    memcpy(prevKeyboardState, keyboardState, keyLength);
    prevMouseState = mouseState;
}
