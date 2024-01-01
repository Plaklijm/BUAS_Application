#include "PlayState.h"

#include "../src/Player/player.h"
#include "../src/Map/World.h"
#include "../src/Player/InputManager.h"


void PlayState::Init()
{
    printf("PlayState init\n");
    world = new World();
    player = new Player(InputManager::Instance(), world);
}

void PlayState::Exit()
{
    printf("PlayState exit\n");
    
}

void PlayState::Pause()
{
}

void PlayState::Continue()
{
}

void PlayState::Update(float deltaTime)
{
    player->Update(deltaTime);
}

void PlayState::PhysUpdate(float pDeltaTime)
{
    player->UpdatePhysics(pDeltaTime);
}

void PlayState::Render(Tmpl8::Surface* screen)
{
    world->RenderMap(screen);
    player->RenderPlayer(screen);
}
