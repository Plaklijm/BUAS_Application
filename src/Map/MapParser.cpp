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
    TiXmlDocument xmlDoc;
    xmlDoc.LoadFile(source);
    
    if (xmlDoc.Error())
    {
        printf("Failed to load: %s\n", source.c_str());
        return false;
    }

    TiXmlElement* root = xmlDoc.RootElement();
    int rc, cc, ts = 0;

    root->Attribute("width", &rc);
    root->Attribute("height", &cc);
    root->Attribute("tilewidth", &ts);

    // parse Tilesets
    TileSetList tilesets;
    for (TiXmlElement* e = root->FirstChildElement(); e!= nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("tileset"))
        {
            tilesets.push_back(ParseTileSet(e));
        }
    }

    GameMap* gamemap = new GameMap();
    for (TiXmlElement* e = root->FirstChildElement(); e!= nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("layer"))
        {
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, ts, rc, cc);
            gamemap->mapLayers.push_back(tilelayer);
        }
    }

    maps[mapID] = gamemap;
    return true;
}

TileSet MapParser::ParseTileSet(TiXmlElement* xmlTileSet)
{
    // Read the attributes from the 
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
    TiXmlElement* data;
    for (TiXmlElement* e = xmlLayer->FirstChildElement(); e!= nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("data"))
        {
            data = e;
            break;
        }
    }

    // Parse tile map layer
    std::string matrix (data->GetText());
    std::istringstream iss(matrix);
    std::string id;

    TileMap tilemap(rowCount, std::vector<int>(colCount, 0));

    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            // get every element before a comma and add it to our tilemap
            std::getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tilemap[i][j];

            // if we've reached the end break
            if (!iss.good())
                break;
        }
    }

    return new TileLayer(tileSize, rowCount, colCount, tilemap, tileSets);
}
