#pragma once
#include <map>
#include <memory>

#include "Animation.h"

class AnimationSystem
{
public:
    AnimationSystem(float animRate);

    void AddAnim(int id, std::unique_ptr<Animation> animation);
    void Update();
    void SetCurrentAnim(int id);

    const Tmpl8::Sprite& GetMasterSprite() const;
    void Render(Tmpl8::Surface* screen, float x, float y, bool flip);

private:
    float animationRate;
    int frameToPlay;
    std::map<int, std::unique_ptr<Animation>> animations;
    int currentAnimID;
};
