#pragma once
#include <vector>

class Solid;
class GameMap;

namespace Tmpl8
{
    
class World
{
    
public:
    std::vector<Solid> GetAllSolidsInCurrentLevel();
    World(int amount);
    void DrawTiles(class Surface* surface);

    Surface* screen;
private:
    std::vector<Solid> tiles;

   GameMap* levelMap;
};
}
