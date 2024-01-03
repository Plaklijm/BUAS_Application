#pragma once
#include "State.h"
#include "../template.h"


class PlayState : public State
{
public:
    void Init(Tmpl8::Game* game) override;
    void Exit() override;
    void Pause() override;
    void Continue() override;
    void Update(float deltaTime) override;
    void PhysUpdate(float pDeltaTime) override;
    void Render(Tmpl8::Surface* screen) override;

    void InitializeWorld();
    
    static PlayState* Instance() {
        return &playState;
    }

private:
    static PlayState playState;
    
    class Player* player;
    class World* world;

    Tmpl8::vec2 playerStartPos;

    int levelIndex;
};
