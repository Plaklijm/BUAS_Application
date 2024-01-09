#include "PlayState.h"

#include <SDL_mouse.h>

#include "game.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "../surface.h"
#include "../src/Engine/Object.h"
#include "../src/Map/World.h"
#include "../src/Player/player.h"
#include "../src/Player/PlayerInventory.h"
#include "Engine/Collision.h"
// ^^ oof big includes for not that much code (dev brain goes brrr)

PlayState PlayState::playState;

bool playDeathSound = true;

void PlayState::Init(Tmpl8::Game* game)
{
    State::Init(game);

    // One is created at the start of the playstate, this isn't done in the player
    // Because when the player respawns a new player is created
    inv = new PlayerInventory();
    
    world = new World();
    levelIndex = 0;
    InitializeWorld();

    SDL_ShowCursor(0);
}

void PlayState::Update(float deltaTime)
{
    if (InputManager::Instance()->KeyDown(SDL_SCANCODE_ESCAPE))
    {
        gameRef->PushState(PauseState::Instance());
    }
    
    player->Update(deltaTime);

    // Reset the player and world when the player falls out of the world
    if (player->GetPosition().y > 750)
    {
        if (playDeathSound)
        {
            playDeathSound = false;
            SoundManager::Instance()->PlaySound(s_DEATH);
        }
        if (player->GetPosition().y > 1250)
        {
            playDeathSound = true;
            InitializeWorld();
        }
    }
}

void PlayState::PhysUpdate(float pDeltaTime)
{
    player->UpdatePhysics(pDeltaTime);
    
    HandleObjects();
}

void PlayState::Render(Tmpl8::Surface* screen)
{
    world->RenderMap(screen);
    
    if (levelIndex == 0)
    {
        PrintTutorial(screen);
    }

    // Render player on top
    player->RenderPlayer(screen);
}

void PlayState::InitializeWorld()
{
    if (!world->LoadMap(levelIndex))
    {
        // Go to main menu if we cant load a map
        gameRef->ChangeState(MainMenuState::Instance());
        return;
    }

    // Initialize all the objects in the world 
    InitializeObjects();

    inv->Reset();
    player = new Player(playerStartPos, InputManager::Instance(), world);
}


void PlayState::PrintTutorial(Tmpl8::Surface* screen)
{
    screen->Print("A-D to move", 33, 340, 0xffffff);
    screen->Print("Shift to walk/slowdown", 33, 360, 0xffffff);
    screen->Print("ESC to pause the game", 33, 380, 0xffffff);

    screen->Print("Press W while moving", 510, 375, 0xffffff);
    screen->Print("To push or pull", 510, 385, 0xffffff);

    screen->Print("Space to jump x2", 420, 300, 0xffffff);
        
    screen->Print("Collect", 665, 400, 0xffffff);
    screen->Print("Collect", 635, 245, 0xffffff);

    screen->Print("Collect them all", 820, 215, 0xffffff);
    screen->Print("to advance", 820, 225, 0xffffff);
}


// Gets all the objects in the gameMap and initializes them with a sprite, also gets the amount needed to collect
// Before you can advance to the new level
void PlayState::InitializeObjects()
{
    std::vector<Object*> allObjects;
    
    for (const auto layer : world->GetMap()->GetMapLayers())
    {
        if (layer->GetIsObjectLayer())
        {
            allObjects = layer->GetObjectTiles();
            amountNeeded = layer->GetCollectableCount();
            break;
        }
    }

    // Another place (Like the map parser) wouldve been better, but out of convenience i put it here so i could get the startpos
    for (const auto object : allObjects)
    {
        switch (object->GetType())
        {
        case PLAYERSTART:
            playerStartPos = object->GetPosition();
            break;
        case PLAYEREND:
            object->SetSprite(new Tmpl8::Sprite(new Tmpl8::Surface("assets/map/playerEnd.png"), 24));
            break;
        case COLLECTABLE:
            object->SetSprite(new Tmpl8::Sprite(new Tmpl8::Surface(sources[rand() % 5]), 1));
            break;
        case PUSHABLE:
            object->SetSprite(new Tmpl8::Sprite(new Tmpl8::Surface("assets/map/Pushable.png"), 1));
            break;
        }
    }
}

// Check for World Object collision
void PlayState::HandleObjects()
{
    const auto obj = Collision::RectIntersectObjects(&player->GetCollider()->GetHitBox(), world);
    if (obj != nullptr)
    {
        if (obj->GetType() == PLAYEREND && inv->HasCollectedAll(amountNeeded))
        {
            SoundManager::Instance()->PlaySound(s_LEVELFINISH);

            // Load the next level
            levelIndex++;
            world->LoadMap(levelIndex);
            InitializeWorld();
        }
        
        if (obj->GetType() == COLLECTABLE)
        {
            // Collect an object
            world->Collect(obj);
            inv->AddCollected();
            player->Collect();
        }
    }
}