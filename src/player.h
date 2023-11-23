#pragma once
#include "PhysEntity.h"
#include "surface.h"

enum anims
{
    A_Idle,
    A_Walk,
    A_Jump
};

enum playerState
{
    S_Idle,
    S_Walk,
    S_Jump,
};

class Player : public PhysEntity
{
private:
    // LOOK FOR A PLACE TO PUT THESE
    unsigned int frame = 0;
    float animationTime{};
    float animationSpeed = .1f;
private:
    Sprite* sprite;

    anims currentAnim;

protected:
    bool currentInput[];
    bool prevInput[];
public:
    Player();
    ~Player() override;

    void UpdatePlayer(float dt);
    void SwitchAnim(anims animToPlay);

private:
    void UpdateAnim(float dt);

public:
    void UpdatePhysics(float dt) override;
};
