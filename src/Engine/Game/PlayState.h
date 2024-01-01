#pragma once
#include "State.h"

class PlayState : public State
{
public:
    void Init() override;
    void Exit() override;
    void Pause() override;
    void Continue() override;
    void Update(float deltaTime) override;
    void PhysUpdate(float pDeltaTime) override;
    void Render(Tmpl8::Surface* screen) override;

private:
    class Player* player;
    class World* world;
};
