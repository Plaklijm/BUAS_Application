#pragma once
#include "Button.h"
#include "GameState.h"

class PauseState : public State
{
public:
    void Init(Tmpl8::Game* game) override;
    void Exit() override;
    void Update(float deltaTime) override;
    void Render(Tmpl8::Surface* screen) override;

    static PauseState* Instance() {
        return &pauseState;
    }
private:
    static PauseState pauseState;

    void ContinueGame() const;
    void RestartLevel();
    void BackToMenu() const;
    
    Button* continueButton;
    Button* restartButton;
    Button* mainMenuButton;
};
