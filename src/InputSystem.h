#pragma once
#include <SDL2-2.28.5/include/SDL_keycode.h>
#include <SDL2-2.28.5/include/SDL_gamecontroller.h>
#include <unordered_map>

enum class ActionType
{
    NO_MOVEMENT,
    MOVE_LEFT,
    MOVE_RIGHT,
    JUMP,
    SPRINT,
};

class InputSystem
{
public:
    InputSystem() = default;
    
    std::unordered_map<SDL_GameControllerButton, ActionType> controllerButtonMapping = {
        {SDL_CONTROLLER_BUTTON_A, ActionType::JUMP},
    };

    std::unordered_map<SDL_GameControllerAxis, ActionType> controllerAxisMapping = {
        {SDL_CONTROLLER_AXIS_LEFTX, ActionType::MOVE_LEFT},
        {SDL_CONTROLLER_AXIS_LEFTX, ActionType::MOVE_RIGHT},
        {SDL_CONTROLLER_AXIS_TRIGGERRIGHT, ActionType::SPRINT}
    };

    std::unordered_map<SDL_Keycode, ActionType> keyboardButtonMapping = {
        {SDL_SCANCODE_A, ActionType::MOVE_LEFT},
        {SDL_SCANCODE_D, ActionType::MOVE_RIGHT},
        {SDL_SCANCODE_SPACE, ActionType::JUMP},
        {SDL_SCANCODE_LSHIFT, ActionType::SPRINT}
    };
};
