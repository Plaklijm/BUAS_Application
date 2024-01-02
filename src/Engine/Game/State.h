#pragma once
#include <cstdio>

namespace Tmpl8
{
    class Game;
    class Surface;
}

class State
{
public:
    virtual void Init(Tmpl8::Game* game) { gameRef = game; }
    virtual void Exit() = 0;

    virtual void Pause() = 0;
    virtual void Continue() = 0;

    // Injection of the game class to handle the switching of the states within the states
    virtual void Update(float deltaTime) = 0;
    virtual void PhysUpdate(float pDeltaTime) {}
    virtual void Render(Tmpl8::Surface* screen) = 0;

protected:
    Tmpl8::Game* gameRef;
};
