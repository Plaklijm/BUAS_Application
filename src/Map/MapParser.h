#pragma once

#include <map>
#include <string>
#include "GameMap.h"
#include "TileLayer.h"
#include "tinyxml/tinyxml.h"

class MapParser
{
public:
    bool Load();
    void Clean();

    GameMap* GetMaps();
    static MapParser* GetInstance() { return instance = (instance != nullptr)? instance : new MapParser(); }

private:
    bool Parse(std::string mapID, std::string source);
    TileSet ParseTileSet(TiXmlElement* xmlTileSet);
    TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TileSetList tileSets, int tileSize, int rowCount, int colCount);
    
private:
    MapParser();
    static MapParser* instance;

    std::map<std::string, GameMap*> maps;
};
