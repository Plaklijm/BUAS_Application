#include "World.h"

vec2 World::GetMapTileAtPoint(vec2 point)
{
}

int World::GetMapTileYAtPoint(float y)
{
}

int World::GetMapTileXAtPoint(float x)
{
    
}

vec2 World::GetMapTilePosition(int tileIndexX, int tileIndexY)
{
    return vec2{float(tileIndexX) * tileSize + position.x,
        float(tileIndexY) * tileSize + position.y};
}
