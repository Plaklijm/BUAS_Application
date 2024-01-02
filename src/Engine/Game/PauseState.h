#pragma once
#include "Button.h"
#include "State.h"

class PauseState : public State
{
public:
    void Init(Tmpl8::Game* game) override;
    void Exit() override;
    void Pause() override;
    void Continue() override;
    void Update(float deltaTime) override;
    void Render(Tmpl8::Surface* screen) override;

    static PauseState* Instance() {
        return &pauseState;
    }
private:
    static PauseState pauseState;

    void ContinueGame();
    void Options();
    void BackToMenu();
    
    Button* continueButton;
    Button* optionsButton;
    Button* mainMenuButton;
};
