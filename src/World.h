#pragma once
#include "SDL2-2.28.5/include/SDL_rect.h"

#include <vector>

class Solid;

namespace Tmpl8
{
    
class World
{
    
public:
    std::vector<Solid> GetAllSolidsInCurrentLevel();
    World(int amount);
    void DrawTiles(class Surface* surface);
    void DrawBox(SDL_Rect cube);

    Surface* screen;
private:
    std::vector<Solid> tiles;
};
}
