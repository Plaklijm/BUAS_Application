#pragma once
#include <SDL2-2.28.5/include/SDL_gamecontroller.h>
#include <SDL2-2.28.5/include/SDL_scancode.h>
#include <string.h>


class InputSystem
{
public:
    // Using a singleton because there will only be one inputsystem for the whole game
    static InputSystem& instance();

    InputSystem();
    ~InputSystem();

private:
    Uint8* prevKeyboardState;
    const Uint8* keyboardState;
    int keyLength;

    Uint8* prevControllerState;
    const Uint8* ControllerState;
    int controllerLenght;
    
public:
    bool KeyDown(SDL_Scancode scanCode) const;
    bool KeyPressed(SDL_Scancode scanCode) const;
    bool KeyReleased(SDL_Scancode scanCode) const;

    bool CButtonDown(SDL_GameControllerButton scanCode) const;
    bool CButtonPressed(SDL_GameControllerButton scanCode) const;
    bool CButtonReleased(SDL_GameControllerButton scanCode) const;

    void Update();
    void UpdatePrevInput();
};
