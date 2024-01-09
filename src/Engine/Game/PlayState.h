#pragma once
#include "GameState.h"
#include "../template.h"


class PlayState : public State
{
public:
    void Init(Tmpl8::Game* game) override;\
    void Update(float deltaTime) override;
    void PhysUpdate(float pDeltaTime) override;
    void Render(Tmpl8::Surface* screen) override;
    
    void InitializeWorld();

    static PlayState* Instance() {
        return &playState;
    }

private:
    void PrintTutorial(Tmpl8::Surface* screen);

    void HandleObjects();

    void InitializeObjects();
    
    static PlayState playState;
    
    class Player* player;
    class World* world;
    class PlayerInventory* inv;

    Tmpl8::vec2 playerStartPos;

    int levelIndex;
    int amountNeeded;

    char* sources[5] = {
        "assets/map/planet1.png",
        "assets/map/planet2.png",
        "assets/map/planet3.png",
        "assets/map/planet4.png",
        "assets/map/planet5.png"
        };
};
