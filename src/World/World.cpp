#include "World.h"

World::World()
{
    
}

World::~World()
{
}

vec2 World::GetMapTileAtPoint(vec2 point)
{
    return vec2{((point.x - position.x + tileSize / 2.0f) / (float)(tileSize)),
                ((point.y - position.y + tileSize / 2.0f) / (float)(tileSize))};
}

int World::GetMapTileYAtPoint(float y)
{
    return int((y - position.x + tileSize / 2.0f) / tileSize);
}

int World::GetMapTileXAtPoint(float x)
{
    return int((x - position.x + tileSize / 2.0f) / tileSize);
}

vec2 World::GetMapTilePosition(int tileIndexX, int tileIndexY)
{
    return vec2{float(tileIndexX) * tileSize + position.x,
        float(tileIndexY) * tileSize + position.y};
}

bool World::IsObstacle(int x, int y) const
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return true;
    
    return tiles[x][y] == Block;
}

bool World::IsGround(int x, int y) const
{
    if (x < 0 || x >= width || y < 0 || y >= height)
       return false;
    
    return tiles[x][y] == Block;
}

bool World::isEmpty(int x, int y) const
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return false;
    
    return tiles[x][y] == Empty;
}

vec3 World::GetPosition() const
{
    return position;
}
