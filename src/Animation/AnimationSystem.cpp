#include "AnimationSystem.h"


AnimationSystem::AnimationSystem(const int animRate) : animationRate(animRate)
{
}

void AnimationSystem::Update(float time, Tmpl8::Sprite* sprite)
{
    currentFrame = static_cast<int>(time / animationRate) % sprite->Frames();
    sprite->SetFrame(currentFrame);
}



