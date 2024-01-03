#include "AnimationSystem.h"

AnimationSystem::AnimationSystem(float animRate) : animationRate(animRate), frameToPlay(0), currentAnimID()
{
}

// first time using the new pointer system, Wanted to give it a shot for sometime and thought maybe could be handy here
void AnimationSystem::AddAnim(int id, std::unique_ptr<Animation> animation)
{
    if (animations.empty())
        currentAnimID = id;
    animations.try_emplace(id, std::move(animation));
}

void AnimationSystem::Update()
{
    animations[currentAnimID]->UpdateAnimation();
}

// TODO Add animation buffer, so for example if you want to play an animation only if the previous has finished, do it here
void AnimationSystem::SetCurrentAnim(int id)
{
    if (currentAnimID != id)
    {
        if (animations[currentAnimID]->IsRunning())
        {
        }
        
        currentAnimID = id;
        animations[currentAnimID]->OnAnimationChange();
    }
}

void AnimationSystem::Render(Tmpl8::Surface* screen, float x, float y, bool flip)
{
    if (animations.find(currentAnimID) != animations.end())
    {
        animations.at(currentAnimID)->RenderAnimation(screen, x, y, flip);
    }
}



