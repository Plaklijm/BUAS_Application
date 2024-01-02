#pragma once
#include <string>

namespace Tmpl8
{
    class Surface;
}

class GameMap;

class World
{
    
public:
    GameMap* GetMap() const;

    World() = default;
    void LoadMap(const std::string& level);
    void RenderMap(Tmpl8::Surface* surface) const;
private:

    GameMap* currentLevel;
};

