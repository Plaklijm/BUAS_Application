#pragma once
#include <map>
#include <memory>

#include "Animation.h"

enum AnimationName : int;

class AnimationSystem
{
public:
    AnimationSystem(float animRate);

    void AddAnim(AnimationName id, std::unique_ptr<Animation> animation);
    void Update();
    void SetCurrentAnim(AnimationName id);

    const Tmpl8::Sprite& GetMasterSprite() const;
    void Render(Tmpl8::Surface* screen, float x, float y, bool flip);

private:
    float animationRate;
    int frameToPlay;
    std::map<AnimationName, std::unique_ptr<Animation>> animations;
    AnimationName currentAnimID;
};
