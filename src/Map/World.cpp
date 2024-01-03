#include "World.h"

#include "MapParser.h"

void World::LoadMap(const int index)
{
    MapParser::GetInstance()->Load(index, this);
    currentLevel = MapParser::GetInstance()->GetMap(index);
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
