#include "Animation.h"

Animation::Animation(Tmpl8::Sprite* sprite, bool loop) : sprite(sprite), loop(loop) , currentFrameIndex(0), frameThreshold(0)
{
    
}

bool loopForever = false;
void Animation::Update(float frameToPlay)
{
    frameThreshold = frameToPlay;
    // The logic for the animation rate will be calculated inside the animation system
    if (!loop && frameThreshold >= sprite->Frames() - 2 || loopForever)
    {
        loopForever = true;
        sprite->SetFrame(sprite->Frames() - 1);
    }
    else
    {
        sprite->SetFrame(frameToPlay);
    }
}

void Animation::OnAnimationChange()
{
    currentFrameIndex = 0;
    frameThreshold = 0;
    loopForever = false;
    // For now, maybe not necessary
}

void Animation::RenderAnimation(Tmpl8::Surface* screen, float x, float y)
{
    sprite->Draw(screen, x, y);
}
