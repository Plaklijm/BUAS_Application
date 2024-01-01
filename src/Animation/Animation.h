#pragma once
#include "../surface.h"

class Animation
{
public:
    Animation(Tmpl8::Sprite* sprite, bool loop = true);
    void Update(float frameToPlay);

    void OnAnimationChange();
    Tmpl8::Sprite* GetSprite() const { return sprite; }

    int GetFrames() const { return sprite->Frames(); }
    void RenderAnimation(Tmpl8::Surface* screen, float x, float y);

private:
    Tmpl8::Sprite* sprite;
    bool loop;
    unsigned int currentFrameIndex;
    unsigned int frameThreshold;
};
