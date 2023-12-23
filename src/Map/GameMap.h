#pragma once

#include <vector>
#include "Layer.h"

class GameMap
{
public:
    GameMap() = default;

    void RenderMap() const
    {
        for (auto layer : mapLayers) {
            layer->Render();
        }
    }

    void UpdateMap() const
    {
        for (auto layer : mapLayers) {
            layer->Update();
        }
    }

    std::vector<Layer*> GetMapLayers() const { return mapLayers; }

private:
    std::vector<Layer*> mapLayers;
};
