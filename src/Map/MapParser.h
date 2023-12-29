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

    GameMap* GetMap(const std::string& id) { return maps[id]; }
    static MapParser* GetInstance() { return instance = (instance != nullptr)? instance : new MapParser(); }

private:
    bool Parse(const std::string& mapID, const std::string& source);
    static TileSet ParseTileSet(TiXmlElement* xmlTileSet);
    static TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, const TileSetList& tileSets, int tileSize, int rowCount, int colCount);
    
private:
    MapParser();
    static MapParser* instance;

    std::map<std::string, GameMap*> maps;
};
