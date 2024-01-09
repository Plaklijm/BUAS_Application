#pragma once
#include "GameMap.h"

namespace Tmpl8
{
    class Surface;
}

class Object;

class World
{
public:
    World() = default;
    bool LoadMap(int index);
    void RenderMap(Tmpl8::Surface* surface) const;

    void Collect(const Object* obj) const;

    GameMap* GetMap() const { return currentLevel; }
private:

    GameMap* currentLevel;
};

