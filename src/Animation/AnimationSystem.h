#pragma once
#include <map>
#include <memory>

#include "Animation.h"
#include "../surface.h"


/*
*       animations.emplace(RUN, new Sprite(new Surface("assets/player/run cycle 48x48.png"), 8));
        animations.emplace(WALK, new Sprite(new Surface("assets/player/PlayerWalk 48x48.png"),8));
        animations.emplace(IDLE, new Sprite(new Surface("assets/player/Character Idle 48x48.png"),10));
        animations.emplace(JUMP, new Sprite(new Surface("assets/player/player jump 48x48.png"),3));
        animations.emplace(DOUBLEJUMP, new Sprite(new Surface("assets/player/player air spin 48x48.png"),6));
 */


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
