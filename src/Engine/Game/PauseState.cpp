#include "PauseState.h"

#include "game.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "../surface.h"
#include "../template.h"
#include "../InputManager.h"

PauseState PauseState::pauseState;

void PauseState::Init(Tmpl8::Game* game)
{
    State::Init(game);
    gameRef->SetIsPaused(true);
    continueButton = new Button(new Tmpl8::Sprite(new Tmpl8::Surface("assets/ui/sprites/Continue.png"), 2), Tmpl8::vec2(100, 100));
    restartButton = new Button(new Tmpl8::Sprite(new Tmpl8::Surface("assets/ui/sprites/Restart.png"), 2), Tmpl8::vec2(100, 175));
    mainMenuButton = new Button(new Tmpl8::Sprite(new Tmpl8::Surface("assets/ui/sprites/MainMenu.png"), 2), Tmpl8::vec2(100, 250));
}

void PauseState::Exit()
{
    gameRef->SetIsPaused(false);
}

void PauseState::Pause()
{
}

void PauseState::Continue()
{
}

void PauseState::Update(float deltaTime)
{
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

void PauseState::ContinueGame()
{
    gameRef->PopState();
}

void PauseState::RestartLevel()
{
    PlayState::Instance()->InitializeWorld();
}

void PauseState::BackToMenu()
{
    gameRef->ChangeState(MainMenuState::Instance());
}
