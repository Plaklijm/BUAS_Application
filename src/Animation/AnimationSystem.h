#pragma once
#include <map>
#include "../surface.h"

/*
*       animations.emplace(RUN, new Sprite(new Surface("assets/player/run cycle 48x48.png"), 8));
        animations.emplace(WALK, new Sprite(new Surface("assets/player/PlayerWalk 48x48.png"),8));
        animations.emplace(IDLE, new Sprite(new Surface("assets/player/Character Idle 48x48.png"),10));
        animations.emplace(JUMP, new Sprite(new Surface("assets/player/player jump 48x48.png"),3));
        animations.emplace(DOUBLEJUMP, new Sprite(new Surface("assets/player/player air spin 48x48.png"),6));
 */


class AnimationSystem
{
public:
    AnimationSystem(int animRate);
    
    void Update(float time, Tmpl8::Sprite* sprite);
    void SetAnim();

private:
    int animationRate;

    int currentFrame;
    int currentAnimFrameCount;

    Tmpl8::Sprite* currentAnim;
};
