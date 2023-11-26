#pragma once
#include "ICommand.h"

class MoveCommand : public ICommand
{
public:
    void Execute() override;
};

class JumpCommand : public ICommand
{
public:
    void Execute() override;
};

class CrouchCommand : public ICommand
{
public:
    void Execute() override;
};