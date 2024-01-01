#include "Animation.h"

Animation::Animation(Tmpl8::Sprite* sprite, float animRate, bool loop) :
    sprite(sprite),
    loop(loop),
    animationRate(animRate),
    currentFrameIndex(0)
{
    
}

void Animation::UpdateAnimation()
{
    if (timer.elapsed() >= animationRate)
    {
        currentFrameIndex++;
        if (currentFrameIndex >= (sprite->Frames() - 1))
        {
            // Handle looping, so when its enabled it sets the index to start over again, otherwise stay at the last frame
            if (loop)
                currentFrameIndex = 0;
            else
                currentFrameIndex = sprite->Frames() -1;
        }
        timer.reset();
    }
    sprite->SetFrame(currentFrameIndex);
}

void Animation::OnAnimationChange()
{
    // Reset animation
    timer.reset();
    currentFrameIndex = 0;
}

void Animation::RenderAnimation(Tmpl8::Surface* screen, float x, float y, bool flip) const
{
    sprite->Draw(screen, x, y, flip);
}

