#include "PlayState.h"

#include "game.h"
#include "../src/Player/player.h"
#include "../src/Map/World.h"
#include "../src/Engine/InputManager.h"

PlayState PlayState::playState;

void PlayState::Init(Tmpl8::Game* game)
{
    State::Init(game);
    
    world = new World();
    world->LoadMap("Level1");
    
    player = new Player(InputManager::Instance(), world);

    gameRef->SetIsPlaying(true);
}

void PlayState::Exit()
{
    
}

void PlayState::Pause()
{
    gameRef->SetIsPlaying(false);
}

void PlayState::Continue()
{
    gameRef->SetIsPlaying(true);
}

void PlayState::Update(float deltaTime)
{
    player->Update(deltaTime);
    if (player->GetPosition().y > 1000)
    {
        player = nullptr;
        player = new Player(InputManager::Instance(), world);
    }
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
