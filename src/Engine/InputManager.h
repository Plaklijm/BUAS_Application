#pragma once
#include <SDL2-2.28.5/include/SDL_keycode.h>

#include "template.h"

// Mostly based on the implementation of https://www.youtube.com/watch?v=YjeIUbzDvDE&list=PLhJr2LOK-xwxQlevIZ97ZABLw72Eu9he7&index=12
// Done it this way to have more functions like KeyPressed and to separate out the input handling and not make it event based

class InputManager
{
public:
    // Using a singleton because there will only be one inputsystem for the whole game
    static InputManager* Instance();
    static void Release();

    void SetWindowParams(bool fullscreen, float windowX, float windowY);

    enum MOUSE_BUTTONS { LEFT = 0, RIGHT, MIDDLE };
private:
    
    InputManager();
    ~InputManager();

    static InputManager* instance;

    bool fullscreen;
    float windowX;
    float windowY;

    // Input state variables
    Uint8* prevKeyboardState;
    const Uint8* keyboardState;
    int keyLength;

    Uint32 prevMouseState;
    Uint32 mouseState;

    int mouseXPos;
    int mouseYPos;

    // Scaled mouse position
    Tmpl8::vec2 actualMousePos;

public:
    // System functions
    void Update();
    void UpdatePrevInput();
    
    // Input functions (stupid key functions think they aren't implemented)
    bool KeyDown(SDL_Scancode scanCode) const;
    bool KeyPressed(SDL_Scancode scanCode) const;
    bool KeyReleased(SDL_Scancode scanCode) const;

    bool MouseButtonDown(MOUSE_BUTTONS button) const;
    bool MouseButtonPressed(MOUSE_BUTTONS button) const;
    bool MouseButtonReleased(MOUSE_BUTTONS button) const;

    Tmpl8::vec2 MousePos() const;
};
