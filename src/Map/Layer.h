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


    // This class got expanded by the needs of the system, this is not the way to do this I think. This class got
    // clunkier everytime i added some functionality 
    bool GetIsCollidable() const                            { return collidable; }
    bool GetIsObjectLayer() const                           { return objectLayer; }
    std::vector<class Solid*> GetCollisionTiles() const     { return collisionTiles; }
    std::vector<class Object*> GetObjectTiles() const       { return objectTiles; }
    int GetCollectableCount() const                         { return collectableCount; }
    
    // Bit ugly but was the only place to put this function (I only have references to this class, not the derived one)
    void RemoveObject(const Object* obj);
protected:
    bool                                                    collidable{};
    bool                                                    objectLayer{};
    std::vector<class Solid*>                               collisionTiles;
    std::vector<class Object*>                              objectTiles;
    int                                                     collectableCount{};
};

inline void Layer::RemoveObject(const Object* obj)
{
    // finds the correct iterator the obj value is residing at and removes it from the vector
    const auto position = std::find(objectTiles.begin(), objectTiles.end(), obj);
    if (position != objectTiles.end())
        objectTiles.erase(position);
}

