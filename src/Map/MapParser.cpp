#include "MapParser.h"

MapParser::MapParser()
{
}

bool MapParser::Load()
{
    return Parse("Level1", "assets/Map/Level1.tmx");
}

void MapParser::Clean()
{
    
}

bool MapParser::Parse(std::string mapID, std::string source)
{
    
}

TileSet MapParser::ParseTileSet(TiXmlElement* xmlTileSet)
{
    TileSet tileset;
    tileset.layerName = xmlTileSet->Attribute("name");
    xmlTileSet->Attribute("firstgid", &tileset.firstID);
    xmlTileSet->Attribute("tilecount", &tileset.tileCount);
    tileset.lastID = (tileset.firstID + tileset.tileCount) - 1;
    
    xmlTileSet->Attribute("columns", &tileset.columns);
    tileset.rows = tileset.tileCount/tileset.columns;
    xmlTileSet->Attribute("tilewidth", &tileset.tileSize);

    const auto image = xmlTileSet->FirstChildElement();
    tileset.source = image->Attribute("source");
    return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TileSetList tileSets, int tileSize, int rowCount,
    int colCount)
{
    
}
