#include "InputSystem.h"

#include <SDL_keyboard.h>

InputSystem& InputSystem::instance()
{
    static auto instance = new InputSystem();
    return *instance;
}

InputSystem::InputSystem()
{
    keyboardState = SDL_GetKeyboardState(&keyLength);
    prevKeyboardState = new Uint8[keyLength];
    memcpy(prevKeyboardState, keyboardState, keyLength);
}

InputSystem::~InputSystem()
{
    delete[] prevKeyboardState;
    prevKeyboardState = nullptr;
}

bool InputSystem::KeyDown(SDL_Scancode scanCode) const
{
    return keyboardState[scanCode];
}

bool InputSystem::KeyPressed(SDL_Scancode scanCode) const
{
    return !prevKeyboardState[scanCode] && keyboardState[scanCode];
}

bool InputSystem::KeyReleased(SDL_Scancode scanCode) const
{
    return prevKeyboardState[scanCode] && !keyboardState[scanCode];
}

void InputSystem::Update()
{
}

void InputSystem::UpdatePrevInput()
{
    memcpy(prevKeyboardState, keyboardState, keyLength);
}
