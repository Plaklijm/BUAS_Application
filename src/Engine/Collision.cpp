#include "Collision.h"

#include <vector>

#include "BoxCollider.h"
#include "Solid.h"
#include "../Map/World.h"
#include "Object.h"

// This collision class is made to extend the functionality of the SDL_Intersect functions by adding normal detection and offset.
// These functions work with the SDL collision functions because they are pretty robust and good enough for my needs,
// therefore I didn't see the necessity to write my own collision functions if they are already provided.
bool Collision::RectIntersect(const SDL_Rect* a, const SDL_Rect* b, Tmpl8::vec2& normal)
{
    // temporary variable to calculate the direction with
    SDL_Rect result{};
    if(SDL_IntersectRect(a, b, &result))
    {
        normal = CalculateNormal(a, result);
        
        return true;
    }
    normal = Tmpl8::vec2::Zero();
    return false; 
}

bool Collision::RectIntersectAt(const SDL_Rect* a, Tmpl8::vec2 offset, const SDL_Rect* b, Tmpl8::vec2& normal)
{
    // Create a new SDL_Rect with the same properties as the a rect
    auto aWithOffset = *a;
    // Add the given offset to the rect
    aWithOffset.x += static_cast<int>(offset.x);
    aWithOffset.y += static_cast<int>(offset.y);
    
    // temporary variable to calculate the direction with
    SDL_Rect result{};
    if(SDL_IntersectRect(&aWithOffset, b, &result))
    {
        normal = CalculateNormal(a ,result);
        
        return true;
    }

    normal = Tmpl8::vec2::Zero();
    return false; 
}

bool Collision::RectIntersectAt(const SDL_Rect* a, Tmpl8::vec2 offset, Tmpl8::vec2& normal, const World* world)
{
    // Create a new SDL_Rect with the same properties as the a rect
    auto aWithOffset = *a;
    // Add the given offset to the rect
    aWithOffset.x += static_cast<int>(offset.x);
    aWithOffset.y += static_cast<int>(offset.y);

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
    
    // Check for all the solids in the level if there was a collision
    for (const auto solid : allSolids)
    {
        // The exact same procedure as the normal RectIntersect
        // temporary variable to calculate the direction with
        SDL_Rect result{};
        // if no intersection has occured skip calculation of normal
        if(!SDL_IntersectRect(&aWithOffset, &solid->GetCollider()->GetHitBox(), &result)) continue;

        normal = CalculateNormal(a ,result);
        
        return true;
    }
    
    normal = Tmpl8::vec2::Zero();
    return false; 
}

Object* Collision::RectIntersectObjects(const SDL_Rect* a, const World* world)
{
    // Check for collisions between the rect and all the objects
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

        // Oof this is ugly
        if (collectable->GetType() >= PLAYEREND)
            return collectable;
    }

    return nullptr;
}

// OVERLOADED VERSION WITH AND OFFSET & COLLISION NORMAL PARAM
Object* Collision::RectIntersectObjects(const SDL_Rect* a, Tmpl8::vec2 offset, Tmpl8::vec2& normal, const World* world)
{
    auto aWithOffset = *a;
    aWithOffset.x += static_cast<int>(offset.x);
    aWithOffset.y += static_cast<int>(offset.y);
    
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
        SDL_Rect result{};
        if (!SDL_IntersectRect(&aWithOffset, &collectable->GetCollider()->GetHitBox(), &result)) continue;

        normal = CalculateNormal(a ,result);
        
        if (collectable->GetType() >= PLAYEREND)
        {
            return collectable;
        }
    }
    
    return nullptr;
}

// Little helper function to make my life easier, and to make this class less bloated (I had this part 3 times, couldn't read shit xD)
Tmpl8::vec2 Collision::CalculateNormal(const SDL_Rect* rect, SDL_Rect result)
{
    Tmpl8::vec2 accumulatedNormal = Tmpl8::vec2::Zero();

    // determine the collision normal
    const auto dx = rect->x + rect->w / 2 - (result.x + result.w / 2);
    const auto dy = rect->y + rect->h / 2 - (result.y + result.h / 2);

    // Check if the collision is more horizontal or more vertical
    // Add to the collision normal (this means we can get the composite, so if you are colliding left and down)
    
    // bug: when colliding with the top half of the player it wil register as vec2::Up(), im not entirely sure why this happens
    // but I solved it with separating the X and Y normals in solo variables. Isn't ideal but i only need bottom half collision anyway
    if (abs(dx) > abs(dy))
    {
        // Horizontal collision
        accumulatedNormal += (dx > 0) ? Tmpl8::vec2::Right() : Tmpl8::vec2::Left();
    }
    else
    {
        // Vertical collision
        accumulatedNormal += (dy > 0) ? Tmpl8::vec2::Down() : Tmpl8::vec2::Up();
    }

    return accumulatedNormal;
}
