#pragma once
#include <vector>

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
    
    bool GetIsCollidable() const                            { return collidable; }
    std::vector<class Solid*> GetCollisionTiles() const     { return collisionTiles; }
protected:
    bool                                                    collidable{};
    std::vector<class Solid*>                               collisionTiles;
};
