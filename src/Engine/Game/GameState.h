#pragma once

namespace Tmpl8
{
    class Game;
    class Surface;
}

class State
{
public:
    virtual void Init(Tmpl8::Game* game) { gameRef = game; }
    virtual void Exit() {}

    // Injection of the game class to handle the switching of the states within the states
    virtual void Update(float deltaTime) {}
    virtual void PhysUpdate(float pDeltaTime) {}
    virtual void Render(Tmpl8::Surface* screen) {}

protected:
    Tmpl8::Game* gameRef;
};
