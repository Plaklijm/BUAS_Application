﻿#include "MapParser.h"

#include "ImageLayer.h"
#include "../src/Engine/Object.h"


MapParser* MapParser::instance = nullptr;

MapParser::MapParser()
{
}

bool MapParser::Load(const int index, World* world)
{
    // Loads a new map
    const auto source = "assets/map/" + std::to_string(index) + ".tmx";
    return Parse(index, source, world);
}

void MapParser::Clean()
{
    std::map<int, GameMap*>::iterator it;
    for (it = maps.begin(); it != maps.end(); it++)
    {
        it->second = nullptr;
    }
    maps.clear();
}

// Start parsing it
bool MapParser::Parse(const int mapID, const std::string& source, World* world)
{
    // Load file
    TiXmlDocument xmlDoc;
    xmlDoc.LoadFile(source);
    
    if (xmlDoc.Error())
    {
        printf("Failed to load: %s\n", source.c_str());
        return false;
    }

    // Get an element to start reading from
    TiXmlElement* root = xmlDoc.RootElement();
    int rc, cc, ts = 0;

    // Parse layer data
    root->Attribute("width", &rc);
    root->Attribute("height", &cc);
    root->Attribute("tilewidth", &ts);

    // Parse Tilesets, this will give all the sprites that need to be loaded to display all the layers (can be more than 1)
    TileSetList tileSets;
    for (TiXmlElement* e = root->FirstChildElement(); e!= nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("tileset"))
        {
            tileSets.push_back(ParseTileSet(e));
        }
    }

    auto* gameMap = new GameMap();

    // Loop through all the elements, and parse the layers and construct them
    for (TiXmlElement* e = root->FirstChildElement(); e!= nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("imagelayer"))
        {
            ImageLayer* imageLayer = ParseImageLayer(e);
            gameMap->mapLayers.push_back(imageLayer);
        }
        else if (e->Value() == std::string("objectgroup"))
        {
            ObjectLayer* objectLayer = ParseObjectLayer(e, world);
            gameMap->mapLayers.push_back(objectLayer);
        }
        else if (e->Value() == std::string("layer"))
        {
            TileLayer* tileLayer = ParseTileLayer(e, tileSets, ts, rc, cc);
            gameMap->mapLayers.push_back(tileLayer);
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
    // Read the layer properties (bit scuffed bit it works) (monkey brain again)
    if (xmlLayer->FirstChildElement()->Value() == std::string("properties")) 
    {
        // Get the property (Bad way to do this, if there are more than 1 property this wont work)
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

ObjectLayer* MapParser::ParseObjectLayer(TiXmlElement* xmlLayer, World* world)
{
    ObjectLayer* layer = new ObjectLayer();
    const auto child = xmlLayer->FirstChildElement();
    
    for (TiXmlElement* e = child; e!= nullptr; e = e->NextSiblingElement())
    {
        // Add each object to the layer
        if (e->Value() == std::string("object"))
        {
            int x, y, size, type;
            e->Attribute("x", &x);
            e->Attribute("y", &y);
            e->Attribute("width", &size);

            if (e->FirstChildElement()->Value() == std::string("properties"))
            {
                // Get the property (again bad way)
                const TiXmlElement* temp = e->FirstChildElement()->FirstChildElement();
                temp->Attribute("value", &type);
            }

            Object* object = new Object(Tmpl8::vec2(x,y), Tmpl8::vec2(size,size), world, static_cast<Type>(type));
            
            layer->AddObject(object);
        }
    }
    
    
    return layer;
}

ImageLayer* MapParser::ParseImageLayer(TiXmlElement* xmlElement)
{
    const auto image = xmlElement->FirstChildElement();
    const std::string img = image->Attribute("source");
    const std::string source = "assets/map/" + img;

    // some magic to convert a string to char* 
    char *csource = new char[source.length() + 1];
    strcpy(csource, source.c_str());
    
    return new ImageLayer(csource);
}
