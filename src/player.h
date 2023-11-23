#pragma once
#include "PhysEntity.h"
#include "surface.h"

enum anims
{
    IDLE,
    WALK,
    CROUCH
};

class Player : public PhysEntity
{
private:
    // LOOK FOR A PLACE TO PUT THESE
    unsigned int frame = 0;
    float animationTime{};
    float animationSpeed = .1f;
private:
    Tmpl8::Sprite* sprite;

    anims currentAnim;
public:
    Player();
    ~Player();

    void UpdatePlayer(float dt);
    void SwitchAnim(anims animToPlay);

private:
    void UpdateAnim(float dt);

public:
    void UpdatePhysics(float dt) override;
};
