#pragma once

class Layer
{
public:
    // pure virtual, the class that inherits this one MUST implement these functions
    virtual void Render() = 0;
    virtual void Update() = 0;
};
