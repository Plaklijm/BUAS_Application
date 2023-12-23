#include "TileLayer.h"

TileLayer::TileLayer(int tileSize, int rowCount, int colCount, const TileMap& tileMap, const TileSetList& tileSetList)
: tileSets(tileSetList)
{
    this->tileSize = tileSize;
    this->rowCount = rowCount;
    this->colCount = colCount;
    this->tileMap = tileMap;

    // Load the texture
}

void TileLayer::Render()
{
    for (unsigned int i = 0; i < rowCount; i++)
    {
        for (unsigned int j = 0; j < rowCount; j++)
        {
            int tileID = tileMap[i][j];
            // continue if there is an empty tile
            if (tileID == 0) continue;
            
            int index;
            if (tileSets.size() > 1)
            {
                for (unsigned int k = 0; k < tileSets.size(); k++)
                {
                    if (tileID > tileSets[k].firstID && tileID < tileSets[k].lastID)
                    {
                        tileID = tileID + tileSets[k].tileCount - tileSets[k].lastID;
                        index = k;
                        break;
                    }
                }
            }

            TileSet ts = tileSets[index];
            int tileRow = tileID/ts.columns;
            int tileCol = tileID - tileRow * ts.columns - 1;

            // If the current tile is on the last column
            if (tileID % ts.columns == 0)
            {
                tileRow--;
                tileCol = ts.columns -1;
            }
        }
    }
}

void TileLayer::Update()
{
}
