#pragma once

#include <map>
#include <string>
#include "GameMap.h"
#include "ObjectLayer.h"
#include "TileLayer.h"
#include "tinyxml/tinyxml.h"

class ImageLayer;
class World;

class MapParser
{
public:
    void Load(const int index, World* world);
    void Clean();

    GameMap* GetMap(const int id) { return maps[id]; }
    static MapParser* GetInstance() { return instance = (instance != nullptr)? instance : new MapParser(); }

private:
    void Parse(const int mapID, const std::string& source, World* world);
    static TileSet ParseTileSet(TiXmlElement* xmlTileSet);
    static TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, const TileSetList& tileSets, int tileSize, int rowCount, int colCount);
    static ObjectLayer* ParseObjectLayer(TiXmlElement* xmlLayer, World* world);
    static ImageLayer* ParseImageLayer(TiXmlElement* xmlElement);
    
private:
    MapParser();
    static MapParser* instance;

    std::map<int, GameMap*> maps;
};
