#include "PlayState.h"

#include "game.h"
#include "MainMenuState.h"
#include "../Collision.h"
#include "../SoundManager.h"
#include "../surface.h"
#include "../../Map/GameMap.h"
#include "../src/Engine/Object.h"
#include "../src/Player/player.h"
#include "../src/Player/PlayerInventory.h"
#include "../src/Map/World.h"
#include "../src/Engine/InputManager.h"


PlayState PlayState::playState;


void PlayState::Init(Tmpl8::Game* game)
{
    State::Init(game);
    
    world = new World();
    levelIndex = 0;
    InitializeWorld();

    // One is created at the start of the playstate, this isn't done in the player
    // Because when the player respawns a new player is created
    inv = new PlayerInventory();

    
    gameRef->SetIsPlaying(true);
}

void PlayState::Exit()
{
    gameRef->SetIsPlaying(false);
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
            if (inv->HasCollectedAll(amountNeeded))
            {
                SoundManager::Instance()->PlaySound(s_LEVELFINISH);
                levelIndex++;
                world->LoadMap(levelIndex);
                InitializeWorld();
                inv->Reset();
            }
            break;
        case COLLECTABLE:
            world->Collect(obj);
            inv->AddCollected();
            player->Collect();
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
    if (!world->LoadMap(levelIndex))
    {
        gameRef->ChangeState(MainMenuState::Instance());
        return;
    }
    
    std::vector<Object*> allObjects;
    
    for (const auto layer : world->GetMap()->GetMapLayers())
    {
        if (layer->GetIsObjectLayer())
        {
            allObjects = layer->GetObjectTiles();
            amountNeeded = layer->GetCollectableCount();
        }
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
        case PUSHABLE:
            object->SetSprite(new Sprite(new Surface("assets/map/Pushable.png"), 1));
            break;
        default:
            break;
        }
    }
    
    player = new Player(playerStartPos, InputManager::Instance(), world);
}
