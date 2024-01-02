#include "World.h"

#include "MapParser.h"

void World::LoadMap(const std::string& level)
{
    MapParser::GetInstance()->Load(level);
    currentLevel = MapParser::GetInstance()->GetMap(level);
}

void World::RenderMap(Tmpl8::Surface* surface) const
{
    currentLevel->RenderMap(surface);
}

GameMap* World::GetMap() const
{
    return currentLevel;
}
