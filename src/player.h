#pragma once
#include <vector>

#include "PhysEntity.h"
#include "surface.h"

/*enum anims
{
    A_Idle,
    A_Walk,
    A_Jump
};*/

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
    /*unsigned int frame = 0;
    float animationTime{};
    float animationSpeed = .1f;*/
private:
    Sprite* sprite;


protected:
    std::vector<bool> currentInput;
    std::vector<bool> prevInput;
public:
    Player();
    ~Player() override;

    void UpdatePlayer(float dt);
    //void SwitchAnim(anims animToPlay);

    void KeyUpEvent(int key, bool isController);
    void KeyDownEvent(int key, bool isController);
    void ControllerJoyStick(vec2 input);
    
private:
    //void UpdateAnim(float dt);

public:
    void UpdatePhysics(float dt) override;
};
