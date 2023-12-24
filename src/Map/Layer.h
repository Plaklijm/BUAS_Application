#pragma once

namespace Tmpl8
{
    class Surface;
}

class Layer
{
public:
    // pure virtual, the class that inherits this one MUST implement these functions
    virtual void Render(Tmpl8::Surface* screen) = 0;
    virtual void Update() = 0;
};
