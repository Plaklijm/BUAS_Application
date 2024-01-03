#pragma once
#include "../Engine/surface.h"
#include "../Engine/template.h"

class Animation
{
public:
    Animation(Tmpl8::Sprite* sprite, float animRate, bool loop = true, bool buffer = false);

    void UpdateAnimation();
    void OnAnimationChange();
    void RenderAnimation(Tmpl8::Surface* screen, float x, float y, bool flip) const;

    bool IsRunning() const { return isRunning; }
private:
    Tmpl8::timer timer;
    Tmpl8::Sprite* sprite;
    bool loop;
    bool buffer;
    float animationRate;
    unsigned int currentFrameIndex;

    bool isRunning;
};
