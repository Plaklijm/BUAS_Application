#include "ImageLayer.h"

#include "../Engine/surface.h"

ImageLayer::ImageLayer(char* source)
{
    backGround = new Tmpl8::Sprite(new Tmpl8::Surface(source), 1);
}

void ImageLayer::Render(Tmpl8::Surface* screen)
{
    backGround->Draw(screen,0,0);
}

void ImageLayer::Update()
{
}
