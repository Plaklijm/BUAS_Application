#pragma once

namespace Tmpl8
{
    class Surface;
}

class Solid;
class GameMap;

class World
{
    
public:
    GameMap* GetMap() const;

    World();
    void RenderMap(Tmpl8::Surface* surface);
private:

    GameMap* levelMap;
};

