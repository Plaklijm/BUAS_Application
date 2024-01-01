#pragma once
#include <cstdio>

namespace Tmpl8
{
    class Surface;
}

class State
{
public:
    virtual void Init() = 0;
    virtual void Exit() = 0;

    virtual void Pause() = 0;
    virtual void Continue() = 0;

    virtual void Update(float deltaTime) = 0;
    virtual void PhysUpdate(float pDeltaTime) {}
    virtual void Render(Tmpl8::Surface* screen) = 0;
};
