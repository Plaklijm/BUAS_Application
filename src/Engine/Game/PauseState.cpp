#include "PauseState.h"

#include <SDL_mouse.h>

#include "game.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "../surface.h"
#include "../InputManager.h"

PauseState PauseState::pauseState;

void PauseState::Init(Tmpl8::Game* game)
{
    State::Init(game);

    //
    continueButton = new Button(new Tmpl8::Sprite(new Tmpl8::Surface("assets/ui/sprites/Continue.png"), 2), Tmpl8::vec2(384, 175));
    restartButton = new Button(new Tmpl8::Sprite(new Tmpl8::Surface("assets/ui/sprites/Restart.png"), 2), Tmpl8::vec2(384, 250));
    mainMenuButton = new Button(new Tmpl8::Sprite(new Tmpl8::Surface("assets/ui/sprites/MainMenu.png"), 2), Tmpl8::vec2(384, 325));
    SDL_ShowCursor(1);
}

void PauseState::Exit()
{
    SDL_ShowCursor(0);
}

void PauseState::Update(float deltaTime)
{
    // Pop this state, we'll return to the playstate
    if (InputManager::Instance()->KeyDown(SDL_SCANCODE_ESCAPE))
    {
        gameRef->PopState();
    }
    
    // Check for Button hover && press
    SDL_Point mousePoint;
    // Create a point to compare to the RECT of the button
    mousePoint.x = InputManager::Instance()->MousePos().x;
    mousePoint.y = InputManager::Instance()->MousePos().y;
    
    if (continueButton->IsHovered(mousePoint) && InputManager::Instance()->MouseButtonDown(InputManager::LEFT))
    {
        const std::function<void()> functionPtr = [this] { ContinueGame(); };
        continueButton->OnPressed(functionPtr);
    }
    if (restartButton->IsHovered(mousePoint) && InputManager::Instance()->MouseButtonDown(InputManager::LEFT))
    {
        const std::function<void()> functionPtr = [this] { RestartLevel(); };
        restartButton->OnPressed(functionPtr);
    }
    if (mainMenuButton->IsHovered(mousePoint) && InputManager::Instance()->MouseButtonDown(InputManager::LEFT))
    {
        const std::function<void()> functionPtr = [this] { BackToMenu(); };
        mainMenuButton->OnPressed(functionPtr);
    }
}

void PauseState::Render(Tmpl8::Surface* screen)
{
    continueButton->DisplayButton(screen);
    mainMenuButton->DisplayButton(screen);
    restartButton->DisplayButton(screen);
}

void PauseState::ContinueGame() const
{
    gameRef->PopState();
}

void PauseState::RestartLevel()
{
    PlayState::Instance()->InitializeWorld();
}

void PauseState::BackToMenu() const
{
    gameRef->ChangeState(MainMenuState::Instance());
}
