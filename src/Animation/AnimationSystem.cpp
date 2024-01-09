#include "AnimationSystem.h"

AnimationSystem::AnimationSystem() : currentAnimID()
{
}

// first time using the new pointer system, Wanted to give it a shot for sometime now and thought maybe could be handy here
void AnimationSystem::AddAnim(int id, std::unique_ptr<Animation> animation)
{
    if (animations.empty())
        currentAnimID = id;
    animations.try_emplace(id, std::move(animation));
}

// Update the current animation
void AnimationSystem::Update()
{
    animations[currentAnimID]->UpdateAnimation();
}

// Set a new animation
void AnimationSystem::SetCurrentAnim(int id)
{
    if (currentAnimID != id)
    {
        currentAnimID = id;
        animations[currentAnimID]->OnAnimationChange();
    }
}

// returns if the given animation is finished playing
bool AnimationSystem::IsAnimFinished(int id)
{
    return animations[id]->IsAnimFinished();
}

// render the current animation on the screen
void AnimationSystem::Render(Tmpl8::Surface* screen, float x, float y, bool flip)
{
    if (animations.find(currentAnimID) != animations.end())
    {
        animations.at(currentAnimID)->RenderAnimation(screen, x, y, flip);
    }
}



