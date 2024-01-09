#include "MainMenuState.h"

#include <SDL_mouse.h>

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
    playButton = new Button(new Tmpl8::Sprite(new Tmpl8::Surface("assets/ui/sprites/Start.png"), 2), Tmpl8::vec2(384, 175));
    creditButton = new Button(new Tmpl8::Sprite(new Tmpl8::Surface("assets/ui/sprites/Credits.png"), 2), Tmpl8::vec2(384, 250));
    quitButton = new Button(new Tmpl8::Sprite(new Tmpl8::Surface("assets/ui/sprites/Quit.png"), 2), Tmpl8::vec2(384, 325));
    backButton = new Button(new Tmpl8::Sprite(new Tmpl8::Surface("assets/ui/sprites/Back.png"), 2), Tmpl8::vec2(384, 400));
    SDL_ShowCursor(1);
}

void MainMenuState::Update(float deltaTime)
{
    // Check for Button hover && press
    SDL_Point mousePoint;
    // Create a point to compare to the RECT of the button
    mousePoint.x = InputManager::Instance()->MousePos().x;
    mousePoint.y = InputManager::Instance()->MousePos().y;

    if (!showCredits)
    {
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
    else
    {
        if (backButton->IsHovered(mousePoint) && InputManager::Instance()->MouseButtonDown(InputManager::LEFT))
        {
            const std::function<void()> functionPtr = [this] { Back(); };
            backButton->OnPressed(functionPtr);
        }
    }
}

void MainMenuState::Render(Tmpl8::Surface* screen)
{
    if (!showCredits)
    {
        playButton->DisplayButton(screen);
        creditButton->DisplayButton(screen);
        quitButton->DisplayButton(screen);
    }
    else
    {
        screen->Print("Game Made By:", 394, 150, 0xffffff);
        screen->Print("Michiel van den Broek", 374, 165, 0xffffff);

        screen->Print("Game Made For:", 394, 195, 0xffffff);
        screen->Print("BUAS", 420, 210, 0xffffff);

        screen->Print("Game Made In:", 394, 240, 0xffffff);
        screen->Print("Cpp", 425, 255, 0xffffff);
        screen->Print("Using the BUAS Template", 368, 265, 0xffffff);
        screen->Print("JetBrains Rider", 386, 275, 0xffffff);
        
        screen->Print("Assets By:", 400, 305, 0xffffff);
        screen->Print("Rumblecade - Lunar Surface 1-B", 358, 320, 0xffffff);
        screen->Print("ZeggyGames - 2d Pixelart Character", 358, 330, 0xffffff);
        screen->Print("Deep-Fold - Pixel Space Generator", 364, 340, 0xffffff);
        screen->Print("Penusbmic - Pixel UI", 364, 350, 0xffffff);
        
        backButton->DisplayButton(screen);
    }
}

void MainMenuState::Credit()
{
    showCredits = true;
    
}

void MainMenuState::Back()
{
    showCredits = false;
}

void MainMenuState::ExitGame() const
{
    gameRef->SetExitApp(1);
}

void MainMenuState::StartGame() const
{
    gameRef->ChangeState(PlayState::Instance());
}
