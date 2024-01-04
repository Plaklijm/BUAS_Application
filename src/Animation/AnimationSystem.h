#pragma once
#include <map>
#include <memory>

#include "Animation.h"

class AnimationSystem
{
public:
    AnimationSystem();

    void AddAnim(int id, std::unique_ptr<Animation> animation);
    void Update();
    void SetCurrentAnim(int id);
    
    void Render(Tmpl8::Surface* screen, float x, float y, bool flip);

private:
    std::map<int, std::unique_ptr<Animation>> animations;
    int currentAnimID;
};
