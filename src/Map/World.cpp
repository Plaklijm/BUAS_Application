#include "World.h"

#include "MapParser.h"
#include "../Engine/surface.h"

World::World()
{
    if (!MapParser::GetInstance()->Load())
    {
        printf("Failed to load map");
    }
    levelMap = MapParser::GetInstance()->GetMap("Level1");
}
    
void World::RenderMap(Tmpl8::Surface* surface)
{
    levelMap->RenderMap(surface);
}

GameMap* World::GetMap() const
{
    return levelMap;
}
