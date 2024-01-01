#include "InputManager.h"

#include <cstring>
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

InputManager::InputManager()
{
    keyboardState = SDL_GetKeyboardState(&keyLength);
    prevKeyboardState = new Uint8[keyLength];
    memcpy(prevKeyboardState, keyboardState, keyLength);

    // TODO: Figure out how to query controller events/state
    /*controllerState = SDL_GameControllerEventState(&controllerLength);
    prevControllerState = new Uint8[controllerLength];
    memcpy(prevControllerState, controllerState, controllerLength);*/
}

InputManager::~InputManager()
{
    delete[] prevKeyboardState;
    prevKeyboardState = nullptr;
}

// -----------------------------------------------------------
// Keyboard Events
// -----------------------------------------------------------
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

// -----------------------------------------------------------
// Controller Events
// -----------------------------------------------------------
#ifdef false
bool InputManager::CButtonDown(SDL_GameControllerButton scanCode) const
{
    return !prevControllerState[scanCode] && ControllerState[scanCode];
}

bool InputManager::CButtonPressed(SDL_GameControllerButton scanCode) const
{
    return ControllerState[scanCode];
}

bool InputManager::CButtonReleased(SDL_GameControllerButton scanCode) const
{
    return prevControllerState[scanCode] && !ControllerState[scanCode];
}
#endif
    
void InputManager::Update()
{
}

void InputManager::UpdatePrevInput() const
{
    memcpy(prevKeyboardState, keyboardState, keyLength);
}
