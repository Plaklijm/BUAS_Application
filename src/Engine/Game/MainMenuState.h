#pragma once
#include "GameState.h"


class Button;

class MainMenuState : public State
{
public:
    void Init(Tmpl8::Game* game) override;
    void Update(float deltaTime) override;
    void Render(Tmpl8::Surface* screen) override;

    static MainMenuState* Instance() {
        return &mainMenuState;
    }
private:
    static MainMenuState mainMenuState;
    
    void StartGame() const;
    void Credit();
    void Back();
    void ExitGame() const;

    Button* playButton;
    Button* creditButton;
    Button* quitButton;
    Button* backButton;

    bool showCredits;
};
