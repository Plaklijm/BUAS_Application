#pragma once

#include <map>
#include <string>
#include "GameMap.h"
#include "ObjectLayer.h"
#include "TileLayer.h"
#include "tinyxml/tinyxml.h"

// This class reads the complete .TMX file of the TILED map
// For this i did follow a tutorial series: https://www.youtube.com/watch?v=3DKriWbJJ50&t=431s ep 15/16/17
// I've never worked with a parser before so i needed some guidance with it
// I added the ImageLayer and object layer Myself and optimized/changed some parts where I thought that needed it

class ImageLayer;
class World;

class MapParser
{
public:
    bool Load(const int index, World* world);
    void Clean();

    GameMap* GetMap(const int id) { return maps[id]; }
    static MapParser* GetInstance() { return instance = (instance != nullptr)? instance : new MapParser(); }

private:
    bool Parse(const int mapID, const std::string& source, World* world);
    static TileSet ParseTileSet(TiXmlElement* xmlTileSet);
    static TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, const TileSetList& tileSets, int tileSize, int rowCount, int colCount);
    static ObjectLayer* ParseObjectLayer(TiXmlElement* xmlLayer, World* world);
    static ImageLayer* ParseImageLayer(TiXmlElement* xmlElement);
    
private:
    MapParser();
    static MapParser* instance;

    std::map<int, GameMap*> maps;
};
