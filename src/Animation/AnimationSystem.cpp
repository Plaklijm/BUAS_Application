#include "AnimationSystem.h"

#include <string>
// first time using the new pointer system, Wanted to give it a shot for sometime and thought maybe could be handy here

AnimationSystem::AnimationSystem(float animRate) : animationRate(animRate), frameToPlay(0)
{
}

void AnimationSystem::AddAnim(AnimationName id, std::unique_ptr<Animation> animation)
{
    if (animations.empty())
        currentAnimID = id;
    animations.try_emplace(id, std::move(animation));
}

void AnimationSystem::Update(float time)
{
    const auto frameCount = animations[currentAnimID]->GetFrames();
    frameToPlay = static_cast<int>(time / animationRate) % frameCount;
    animations[currentAnimID]->Update(frameToPlay);
}

void AnimationSystem::SetCurrentAnim(AnimationName id)
{
    if (currentAnimID != id)
    {
        currentAnimID = id;
        animations[currentAnimID]->OnAnimationChange();
    }
}

void AnimationSystem::Render(Tmpl8::Surface* screen, float x, float y)
{
    if (animations.find(currentAnimID) != animations.end())
    {
        animations.at(currentAnimID)->RenderAnimation(screen, x, y);
    }
}



