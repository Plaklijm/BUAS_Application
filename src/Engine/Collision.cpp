#include "Collision.h"

#include <vector>

#include "BoxCollider.h"
#include "Solid.h"
#include "../Map/World.h"
#include "../Map/GameMap.h"
#include "Object.h"

// This collision class is made to extend the functionality of the SDL_Intersect functions by adding normal detection and offset.
// These functions work with the SDL collision functions because they are pretty robust and good enough for my needs,
// therefore I didn't see the necessity to write my own collision functions if they are already provided.
bool Collision::RectIntersect(const SDL_Rect* a, const SDL_Rect* b, vec2& normal)
{
    // temporary variable to calculate the direction with
    SDL_Rect result{};
    if(SDL_IntersectRect(a, b, &result))
    {
        // Collision has occurred, now to determine the collision normal
        const auto dx = a->x + a->w / 2 - (result.x + result.w / 2);
        const auto dy = a->y + a->h / 2 - (result.y + result.h / 2);

        // Check if the collision is more horizontal or vertical
        if (abs(dx) > abs(dy))
        {
            // Horizontal collision
            if (dx > 0) 
                normal = vec2::Right();
            else 
                normal = vec2::Left();
        }
        else
        {
            // Vertical collision
            if (dy > 0)
                normal = vec2::Down();
            else
                normal = vec2::Up();
        }
        
        return true;
    }
    normal = vec2::Zero();
    return false; 
}

bool Collision::RectIntersectAt(const SDL_Rect* a, vec2 aOffset, vec2& normal, const World* world)
{
    // Create a new SDL_Rect with the same properties as the a rect
    auto aWithOffset = *a;
    // Add the given offset to the rect
    aWithOffset.x += static_cast<int>(aOffset.x);
    aWithOffset.y += static_cast<int>(aOffset.y);

    const auto map = world->GetMap();
    std::vector<Solid*> allSolids;
    std::vector<Object*> allObjects;
    
    for (const auto layer : map->GetMapLayers())
    {
        if (layer->GetIsCollidable())
        {
            allSolids = layer->GetCollisionTiles();
            break;
        }
    }
    
    vec2 accumulatedNormal = vec2::Zero();
    // Check for all the solids in the level if there was a collision
    for (const auto solid : allSolids)
    {
        // The exact same procedure as the normal RectIntersect
        // temporary variable to calculate the direction with
        SDL_Rect result{};
        // if no intersection has occured skip calculation of normal
        if(!SDL_IntersectRect(&aWithOffset, &solid->GetCollider()->GetHitBox(), &result)) continue;

        // TODO HELPER FUNCTION THAT CALCULATES THE NORMAL
        // Collision has occurred, now to determine the collision normal
        const auto dx = a->x + a->w / 2 - (result.x + result.w / 2);
        const auto dy = a->y + a->h / 2 - (result.y + result.h / 2);

        // Check if the collision is more horizontal or more vertical
        // Add to the collision normal (this means we can get the composite, so if you are colliding left and down)
        // BUG: when colliding with the top half of the player it wil register as vec2::Up(), im not entirely sure why this happens
        // BUG: but I solved it with separating the X and Y normals in solo variables. Isn't ideal but i only need bottom half collision anyway
        if (abs(dx) > abs(dy))
        {
            // Horizontal collision
            accumulatedNormal += (dx > 0) ? vec2::Right() : vec2::Left();
        }
        else
        {
            // Vertical collision
            accumulatedNormal += (dy > 0) ? vec2::Down() : vec2::Up();
        }

        
        normal = accumulatedNormal;
        return true;
    }

    // no collision, so false and no normal are returned
    normal = vec2::Zero();
    return false; 
}

Object* Collision::RectIntersectObjects(const SDL_Rect* a, const World* world)
{
    const auto map = world->GetMap();
    std::vector<Object*> allObjects;
    
    for (const auto layer : map->GetMapLayers())
    {
        if (layer->GetIsObjectLayer())
        {
            allObjects = layer->GetObjectTiles();
            break;
        }
    }

    for (const auto collectable : allObjects)
    {
        if (!SDL_HasIntersection(a, &collectable->GetCollider()->GetHitBox())) continue;

        if (collectable->GetType() >= PLAYEREND)
            return collectable;
    }

    return nullptr;
}

// OVERLOADED VERSION WITH AND OFFSET & COLLISION NORMAL PARAM
Object* Collision::RectIntersectObjects(const SDL_Rect* a, vec2 aOffset, vec2& normal, const World* world)
{
    auto aWithOffset = *a;
    aWithOffset.x += static_cast<int>(aOffset.x);
    aWithOffset.y += static_cast<int>(aOffset.y);
    
    const auto map = world->GetMap();
    std::vector<Object*> allObjects;
    
    for (const auto layer : map->GetMapLayers())
    {
        if (layer->GetIsObjectLayer())
        {
            allObjects = layer->GetObjectTiles();
            break;
        }
    }
    
    vec2 accumulatedNormal = vec2::Zero();
    for (const auto collectable : allObjects)
    {
        SDL_Rect result{};
        if (!SDL_IntersectRect(&aWithOffset, &collectable->GetCollider()->GetHitBox(), &result)) continue;

        const auto dx = a->x + a->w / 2 - (result.x + result.w / 2);
        const auto dy = a->y + a->h / 2 - (result.y + result.h / 2);
        
        if (abs(dx) > abs(dy))
        {
            // Horizontal collision
            accumulatedNormal += (dx > 0) ? vec2::Right() : vec2::Left();
        }
        else
        {
            // Vertical collision
            accumulatedNormal += (dy > 0) ? vec2::Down() : vec2::Up();
        }
        
        if (collectable->GetType() >= PLAYEREND)
        {
            normal = accumulatedNormal;
            return collectable;
        }
    }
    
    normal = vec2::Zero();
    return nullptr;
}
