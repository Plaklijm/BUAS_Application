#pragma once
#include "../Engine/surface.h"
#include "../Engine/template.h"

class Animation
{
public:
    Animation(Tmpl8::Sprite* sprite, float animRate, bool loop = true);

    void UpdateAnimation();
    void OnAnimationChange();
    void RenderAnimation(Tmpl8::Surface* screen, float x, float y, bool flip) const;

private:
    Tmpl8::timer timer;
    Tmpl8::Sprite* sprite;
    bool loop;
    float animationRate;
    unsigned int currentFrameIndex;
};
