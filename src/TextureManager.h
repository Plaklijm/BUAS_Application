#pragma once
#include <map>
#include <string>

#include "surface.h"

class TextureManager
{
public:
    TextureManager(Tmpl8::Surface* targetSurface) : targetSurface(targetSurface) {}

    bool Load(std::string id, std::string fileName);
    void DrawTile(Tmpl8::Sprite* sprite, int x, int y, int row, int frame);

private:
    std::map<std::string, Tmpl8::Sprite*> TextureMap;
    Tmpl8::Surface* targetSurface;
};
