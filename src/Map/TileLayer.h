#pragma once

#include "Layer.h"
#include <string>
#include "../surface.h"

class Solid;

struct TileSet
{
    int firstID;
    int lastID;
    int tileCount;
    int tileSize;
    std::string layerName;
    std::string source;
};

struct tile
{
    Tmpl8::Sprite* sprite;
    int frame;
    int posX;
    int posY;
};

using TileSetList = std::vector<TileSet>;
using TileMap = std::vector<std::vector<int> >;

class TileLayer : public Layer
{
public:
    void CalculateSpriteData();
    TileLayer(bool collidable, int tileSize, int rowCount, int colCount, TileMap tileMap, const TileSetList& tileSetList);

    void Render(Tmpl8::Surface* screen) override;
    void Update() override;

    TileMap GetTileMap() const      { return tileMap; }
private:
    void SetupCollisionLayer();
    
    int                             tileSize;
    int                             rowCount;
    int                             colCount;
    TileMap                         tileMap;
    TileSetList                     tileSets;
    std::vector<Tmpl8::Sprite*>     textures;
    std::vector<tile>               tiles;
};
