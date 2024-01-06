#pragma once
#include <map>
#include <memory>

#include "Animation.h"

class AnimationSystem
{
public:
    AnimationSystem();

    void Update();
    void Render(Tmpl8::Surface* screen, float x, float y, bool flip);
    
    void AddAnim(int id, std::unique_ptr<Animation> animation);
    void SetCurrentAnim(int id);
    bool IsAnimFinished(int id);
    
private:
    std::map<int, std::unique_ptr<Animation>> animations;
    int currentAnimID;
};
