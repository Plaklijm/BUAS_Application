#include "World.h"

#include "MapParser.h"

bool World::LoadMap(const int index)
{
    if (!MapParser::GetInstance()->Load(index, this))
    {
        return false;
    }
    
    currentLevel = MapParser::GetInstance()->GetMap(index);
    return true;
}

void World::RenderMap(Tmpl8::Surface* surface) const
{
    currentLevel->RenderMap(surface);
}

void World::Collect(const Object* obj) const
{
    for (const auto layer : currentLevel->GetMapLayers())
    {
        if (!layer->GetIsObjectLayer()) continue;

        layer->RemoveObject(obj);
    }
}

GameMap* World::GetMap() const
{
    return currentLevel;
}
