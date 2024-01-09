#pragma once

#include <vector>
#include "Layer.h"

class GameMap
{
public:
    GameMap() = default;

    void RenderMap(Tmpl8::Surface* screen) const
    {
        // Render the layers in the order that they are added
        for (const auto layer : mapLayers) {
            layer->Render(screen);
        }
    }

    void UpdateMap() const
    {
        for (const auto layer : mapLayers) {
            layer->Update();
        }
    }

    std::vector<Layer*> GetMapLayers() const { return mapLayers; }
    
private:
    friend class MapParser;
    std::vector<Layer*> mapLayers;

    int collectableAmount;
    bool canGoToNextLevel;
};
