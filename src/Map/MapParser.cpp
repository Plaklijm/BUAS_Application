#include "MapParser.h"

MapParser* MapParser::instance = nullptr;

MapParser::MapParser()
{
}

bool MapParser::Load()
{
    return Parse("Level1", "assets/Map/Level1.tmx");
}

void MapParser::Clean()
{
    std::map<std::string, GameMap*>::iterator it;
    for (it = maps.begin(); it != maps.end(); it++)
    {
        it->second = nullptr;
    }
    maps.clear();
}

bool MapParser::Parse(const std::string& mapID, const std::string& source)
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

    // Parse layer data
    root->Attribute("width", &rc);
    root->Attribute("height", &cc);
    root->Attribute("tilewidth", &ts);

    // Parse Tilesets
    TileSetList tileSets;
    for (TiXmlElement* e = root->FirstChildElement(); e!= nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("tileset"))
        {
            tileSets.push_back(ParseTileSet(e));
        }
    }

    auto* gameMap = new GameMap();
    for (TiXmlElement* e = root->FirstChildElement(); e!= nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("layer"))
        {
            TileLayer* tilelayer = ParseTileLayer(e, tileSets, ts, rc, cc);
            gameMap->mapLayers.push_back(tilelayer);
        }
    }

    maps[mapID] = gameMap;
    return true;
}

TileSet MapParser::ParseTileSet(TiXmlElement* xmlTileSet)
{
    // Read the attributes from the 
    TileSet tileSet;
    tileSet.layerName = xmlTileSet->Attribute("name");
    xmlTileSet->Attribute("firstgid", &tileSet.firstID);
    xmlTileSet->Attribute("tilecount", &tileSet.tileCount);
    tileSet.lastID = (tileSet.firstID + tileSet.tileCount) - 1;
    
    xmlTileSet->Attribute("tilewidth", &tileSet.tileSize);

    const auto image = xmlTileSet->FirstChildElement();
    tileSet.source = image->Attribute("source");

    
    return tileSet;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, const TileSetList& tileSets, int tileSize, int rowCount,
    int colCount)
{
    // Set to null as default value;
    bool collidable = false;
    // Read the layer properties (bit scuffed bit it works)
    if (xmlLayer->FirstChildElement()->Value() == std::string("properties"))
    {
        // Get the property
        TiXmlElement* temp = xmlLayer->FirstChildElement()->FirstChildElement();

        // Tiny XML doesnt support parsing a boolean so 0 is false anything else is true
        int collision{};
        temp->Attribute("value", &collision);

        collidable = collision;
    }
    
    
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

    TileMap tileMap(colCount, std::vector<int>(rowCount, 0));

    for (int i = 0; i < colCount; i++)
    {
        for (int j = 0; j < rowCount; j++)
        {
            // get every element before a comma and add it to our tilemap
            std::getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tileMap[i][j];

            // if we've reached the end break
            if (!iss.good())
                break;
        }
    }

    return new TileLayer(collidable ,tileSize, rowCount, colCount, tileMap, tileSets);
}
