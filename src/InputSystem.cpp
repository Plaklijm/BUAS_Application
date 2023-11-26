#include "InputSystem.h"

#include "ICommand.h"

void InputSystem::HandleInput() const
{
    for (auto keyCommand : keyCommands)
    {
        // check if key is down;
        keyCommand->command->Execute();
    }
}

void InputSystem::BindInputToCommand(int keyCode, ICommand* command)
{
    keyCommands.push_back(new KeyCommand{keyCode, command});
}
