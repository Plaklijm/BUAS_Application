#pragma once
#include <vector>

class ICommand;

struct KeyCommand
{
    int keycode;
    ICommand* command;
};

class InputSystem
{
private:
    std::vector<KeyCommand*> keyCommands;
public:
    InputSystem() = default;

    void HandleInput() const;
    void BindInputToCommand(int keyCode, ICommand* command);
};

