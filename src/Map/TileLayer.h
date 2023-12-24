#pragma once

#include "Layer.h"
#include <vector>
#include <string>

struct TileSet
{
    int firstID;
    int lastID;
    int rows;
    int columns;
    int tileCount;
    int tileSize;
    std::string layerName;
    std::string source;
};

using TileSetList = std::vector<TileSet>;
using TileMap = std::vector<std::vector<int> >;

class TileLayer : public Layer
{
public:
    TileLayer(int tileSize, int rowCount, int colCount, const TileMap& tileMap, const TileSetList& tileSetList);

    virtual void Render(Tmpl8::Surface* screen);
    virtual void Update();

    TileMap GetTileMap()    { return tileMap; }
    
private:
    int                     tileSize;
    int                     rowCount;
    int                     colCount;
    TileMap                 tileMap;
    TileSetList             tileSets;
};
