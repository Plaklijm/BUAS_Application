#pragma once
#include <vector>

class Solid;
class GameMap;

namespace Tmpl8
{
    
class World
{
    
public:
    GameMap* GetMap() const;

    World();
    void RenderMap(class Surface* surface);
private:

    GameMap* levelMap;
};
}
