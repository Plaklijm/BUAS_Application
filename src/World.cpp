#include "World.h"

#include "BoxCollider.h"
#include "Solid.h"
#include "surface.h"

namespace Tmpl8
{
    World::World(int amount)
    {
        vec2 position{0, 128};
        vec2 size = {32,32};
        tiles.emplace_back(position, size);
        
        for (int i = 0; i < amount; ++i)
        {
            vec2 position{size.x * i, 160};
            tiles.emplace_back(position, size);
            printf("Tile = %i,%i\n", tiles[i].GetCollider()->GetHitBox().x, tiles[i].GetCollider()->GetHitBox().y);
        }
        position.x = 608;
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

    std::vector<Solid> World::GetAllSolidsInCurrentLevel()
    {
        // Now you can use the static variable 'tiles' here
        return tiles;
    }
}
