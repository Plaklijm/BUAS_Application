#pragma once
#include <SDL2-2.28.5/include/SDL_keycode.h>
#include <SDL2-2.28.5/include/SDL_gamecontroller.h>

enum class ActionType
{
    NO_MOVEMENT,
    MOVE_LEFT,
    MOVE_RIGHT,
    JUMP,
    SPRINT,
};

// based on the implementation of https://www.youtube.com/watch?v=YjeIUbzDvDE&list=PLhJr2LOK-xwxQlevIZ97ZABLw72Eu9he7&index=12
// Done it this way to have more functions like KeyPressed and to separate out the input handling and not make it event based
// Added controller support to this system and changed it a little bit to work with my own requirements
class InputManager
{
public:
    // Using a singleton because there will only be one inputsystem for the whole game
    static InputManager* Instance();
    static void Release();

    InputManager();
    ~InputManager();

private:
    static InputManager* instance;

    // Input state variables
    Uint8* prevKeyboardState;
    const Uint8* keyboardState;
    int keyLength;

    Uint8* prevControllerState;
    const Uint8* controllerState;
    int controllerLength;

public:
    // System functions
    void Update();
    void UpdatePrevInput() const;
    
    // Input functions
    bool KeyDown(SDL_Scancode scanCode) const;
    bool KeyPressed(SDL_Scancode scanCode) const;
    bool KeyReleased(SDL_Scancode scanCode) const;

    bool CButtonDown(SDL_GameControllerButton scanCode) const;
    bool CButtonPressed(SDL_GameControllerButton scanCode) const;
    bool CButtonReleased(SDL_GameControllerButton scanCode) const;
};
