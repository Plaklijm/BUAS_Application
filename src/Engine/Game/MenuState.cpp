#include "MenuState.h"

#include "../surface.h"

void MenuState::Init()
{
    printf("MenuState init\n");
}

void MenuState::Exit()
{
}

void MenuState::Pause()
{
}

void MenuState::Continue()
{
}

void MenuState::Update(float deltaTime)
{
}

void MenuState::PhysUpdate(float pDeltaTime)
{
}

void MenuState::Render(Tmpl8::Surface* screen)
{
    screen->Print("YOU ARE PAUSED BIATCH", 350, 240, 255 * 255);
}