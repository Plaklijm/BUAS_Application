﻿#include "PlayState.h"

#include "game.h"
#include "../Collision.h"
#include "../surface.h"
#include "../../Map/GameMap.h"
#include "../src/Engine/Object.h"
#include "../src/Player/player.h"
#include "../src/Map/World.h"
#include "../src/Engine/InputManager.h"

PlayState PlayState::playState;


void PlayState::Init(Tmpl8::Game* game)
{
    State::Init(game);

    levelIndex = 1;
    InitializeWorld();


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
        player = new Player(playerStartPos, InputManager::Instance(), world);
    }
    
}

void PlayState::PhysUpdate(float pDeltaTime)
{
    player->UpdatePhysics(pDeltaTime);

    const auto obj = Collision::RectIntersectObjects(&player->GetCollider()->GetHitBox(), world);
    if (obj != nullptr)
    {
        switch (obj->GetType())
        {
        case PLAYEREND:
            levelIndex++;
            world->LoadMap(levelIndex);
            InitializeWorld();
            break;
        case COLLECTABLE:
            world->Collect(obj);
            break;
        default:
            break;
        }
    }
}

void PlayState::Render(Tmpl8::Surface* screen)
{
    world->RenderMap(screen);
    player->RenderPlayer(screen);
}

void PlayState::InitializeWorld()
{
    world = new World();
    world->LoadMap(levelIndex);
    
    std::vector<Object*> allObjects;
    
    for (const auto layer : world->GetMap()->GetMapLayers())
    {
        if (layer->GetIsObjectLayer())
            allObjects = layer->GetObjectTiles();
    }

    char* sources[5] = {
        "assets/map/planet1.png",
        "assets/map/planet2.png",
        "assets/map/planet3.png",
        "assets/map/planet4.png",
        "assets/map/planet5.png"
        };
    
    for (const auto object : allObjects)
    {
        //TODO: SWITCH CASE FOR ALL THE OBJECT TYPES :)
        switch (object->GetType())
        {
        case PLAYERSTART:
            playerStartPos = object->GetPosition();
            break;
        case PLAYEREND:
            object->SetSprite(new Sprite(new Surface("assets/map/playerEnd.png"), 24));
            break;
        case COLLECTABLE:
            object->SetSprite(new Sprite(new Surface(sources[rand() % 5]), 1));
            break;
        default:
            break;
        }
    }

    player = new Player(playerStartPos, InputManager::Instance(), world);
}
