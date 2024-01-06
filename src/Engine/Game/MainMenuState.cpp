#include "MainMenuState.h"

#include <SDL.h>

#include "Button.h"
#include "game.h"
#include "PlayState.h"
#include "../InputManager.h"
#include "../surface.h"
#include "../template.h"

MainMenuState MainMenuState::mainMenuState;

void MainMenuState::Init(Tmpl8::Game* game)
{
    // Set reference to the game
    State::Init(game);
    
    // Initialize background sprite
    
    // Initialize buttons
    playButton = new Button(new Tmpl8::Sprite(new Tmpl8::Surface("assets/ui/sprites/Start.png"), 2), Tmpl8::vec2(335, 100));
    creditButton = new Button(new Tmpl8::Sprite(new Tmpl8::Surface("assets/ui/sprites/Credits.png"), 2), Tmpl8::vec2(335, 250));
    quitButton = new Button(new Tmpl8::Sprite(new Tmpl8::Surface("assets/ui/sprites/Quit.png"), 2), Tmpl8::vec2(335, 325));
}

void MainMenuState::Exit()
{ 
}

void MainMenuState::Pause()
{
}

void MainMenuState::Continue()
{
}

void MainMenuState::Update(float deltaTime)
{
    // Check for Button hover && press
    SDL_Point mousePoint;
    // Create a point to compare to the RECT of the button
    mousePoint.x = InputManager::Instance()->MousePos().x;
    mousePoint.y = InputManager::Instance()->MousePos().y;
    
    if (playButton->IsHovered(mousePoint) && InputManager::Instance()->MouseButtonDown(InputManager::LEFT))
    {
        const std::function<void()> functionPtr = [this] { StartGame(); };
        playButton->OnPressed(functionPtr);
    }
    if (creditButton->IsHovered(mousePoint) && InputManager::Instance()->MouseButtonDown(InputManager::LEFT))
    {
        const std::function<void()> functionPtr = [this] { Credit(); };
        creditButton->OnPressed(functionPtr);
    }
    if (quitButton->IsHovered(mousePoint) && InputManager::Instance()->MouseButtonDown(InputManager::LEFT))
    {
        const std::function<void()> functionPtr = [this] { ExitGame(); };
        quitButton->OnPressed(functionPtr);
    }
}

void MainMenuState::PhysUpdate(float pDeltaTime)
{
}

void MainMenuState::Render(Tmpl8::Surface* screen)
{
    playButton->DisplayButton(screen);
    creditButton->DisplayButton(screen);
    quitButton->DisplayButton(screen);
}

void MainMenuState::Credit()
{
}

void MainMenuState::ExitGame()
{
    gameRef->SetExitApp(1);
}

void MainMenuState::StartGame()
{
    gameRef->ChangeState(PlayState::Instance());
}



// Create button class which contains atleast a SDL_RECT and a sprite, Logic will be made in here
// Functions with Hover, and Click will work on the SDL_PointInRect
// Also create a MenuStats struct (like the player stats) that will contain everything there is to know about the sizing etc
