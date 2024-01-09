#pragma once
#include "Layer.h"

namespace Tmpl8
{
    class Sprite;
}

// Exactly what it says, just a layer that displays an image
class ImageLayer : public Layer
{
public:
    ImageLayer(char* source);
    
    void Render(Tmpl8::Surface* screen) override;
    void Update() override;

private:
    Tmpl8::Sprite* backGround;
};
