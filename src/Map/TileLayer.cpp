#include "TileLayer.h"

TileLayer::TileLayer(int tileSize, int rowCount, int colCount, const TileMap& tileMap, const TileSetList& tileSetList)
{
    this->tileSize = tileSize;
    this->rowCount = rowCount;
    this->colCount = colCount;
    this->tileMap = tileMap;
    this->tileSets = tileSetList;
}
