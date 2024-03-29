﻿#include "ObjectLayer.h"

#include "../src/Engine/Object.h"
#include "../Engine/surface.h"

ObjectLayer::ObjectLayer() 
{
    this->objectLayer = true;
}

void ObjectLayer::Render(Tmpl8::Surface* screen)
{
    for (const auto object : objectTiles)
    {
        object->Render(screen);
    }
}

void ObjectLayer::Update()
{ 
}

void ObjectLayer::AddObject(Object* obj)
{
    objectTiles.emplace_back(obj);
    if (obj->GetType() == COLLECTABLE)
        collectableCount++;
}
