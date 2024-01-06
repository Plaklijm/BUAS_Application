#pragma once

namespace Tmpl8
{
    class Surface;
}

class GameMap;
class Object;

class World
{
    
public:
    GameMap* GetMap() const;

    World() = default;
    bool LoadMap(const int index);
    void RenderMap(Tmpl8::Surface* surface) const;

    void Collect(const Object* obj) const;
private:

    GameMap* currentLevel;
};

