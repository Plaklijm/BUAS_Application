#pragma once
#include "State.h"


class Button;

class MainMenuState : public State
{
public:
    void Init(Tmpl8::Game* game) override;
    void Exit() override;
    void Pause() override;
    void Continue() override;
    void Update(float deltaTime) override;
    void PhysUpdate(float pDeltaTime) override;
    void Render(Tmpl8::Surface* screen) override;

    static MainMenuState* Instance() {
        return &mainMenuState;
    }
private:
    static MainMenuState mainMenuState;
    
    void StartGame();
    void Options();
    void Credit();
    void ExitGame();
    
    Button* playButton;
    Button* optionsButton;
    Button* creditButton;
    Button* quitButton;
};
