#include "World.h"

#include "BoxCollider.h"
#include "Solid.h"
#include "surface.h"

namespace Tmpl8
{
    World::World(int amount)
    {
        vec2 size = {32,32};
        for (int i = 0; i < amount; ++i)
        {
            vec2 position{size.x * i, 64};
            tiles.emplace_back(position, size);
            printf("Tile = %i,%i\n", tiles[i].GetCollider()->GetHitBox().x, tiles[i].GetCollider()->GetHitBox().y);
        }
        vec2 position{288, 32};
        tiles.emplace_back(position, size);
    }

    void World::DrawTiles(Surface* surface)
    {
        screen = surface;
        for (auto tile : tiles)
        {
            auto b1 = tile.GetCollider()->GetHitBox();
            surface->Box(b1.x, b1.y, b1.x + b1.w, b1.y + b1.h, 0xffffff);
        }
    }

    void World::DrawBox(SDL_Rect cube)
    {
        screen->Box(cube.x, cube.y, cube.x + cube.w, cube.y + cube.h, 255);
    }


    std::vector<Solid> World::GetAllSolidsInCurrentLevel()
    {
        // Now you can use the static variable 'tiles' here
        return tiles;
    }

    
}
