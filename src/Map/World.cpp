#include "World.h"

#include "MapParser.h"

namespace Tmpl8
{

    World::World()
    {
        if (!MapParser::GetInstance()->Load())
        {
            printf("Failed to load map");
        }
        levelMap = MapParser::GetInstance()->GetMap("Level1");
    }
    
    void World::RenderMap(Surface* surface)
    {
        //texture.Draw(surface, 0 ,0);
        levelMap->RenderMap(surface);
    }

    GameMap* World::GetMap() const
    {
        return levelMap;
    }
}
