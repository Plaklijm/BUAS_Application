#pragma once
#include "../template.h"

using namespace Tmpl8;

constexpr int width = 80;
constexpr int height = 60;
constexpr int tileSize = 16;

enum TileType
{
    Empty,
    Block
};

class World
{
private:
    vec2 test {10,10};

    TileType tiles[width][height] = {};
    vec3 position;
public:
    World();
    ~World();
    
    vec2 GetMapTileAtPoint(vec2 point);
    int GetMapTileYAtPoint(float y);
    int GetMapTileXAtPoint(float x);
    vec2 GetMapTilePosition(int tileIndexX, int tileIndexY);
    bool IsObstacle(int x, int y) const;
    bool IsGround(int x, int y) const;
    bool isEmpty(int x, int y) const;
    vec3 GetPosition() const;
};
