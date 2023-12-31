#include "Collision.h"

#include <vector>

#include "BoxCollider.h"
#include "Solid.h"
#include "../Map/GameMap.h"
#include "../Map/World.h"

// This collision class is made to extend the functionality of the SDL_Intersect functions by adding normal detection and offset.
// These functions work with the SDL collision functions because they are pretty robust and good enough for my needs,
// therefore I didn't see the necessity to write my own collision functions if they are already provided.
namespace Tmpl8
{
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


    bool Collision::RectIntersectAt(const SDL_Rect* a, vec2 aOffset, vec2& normal, World* world)
    {
        // Create a new SDL_Rect with the same properties as the a rect
        auto aWithOffset = *a;
        // Add the given offset to the rect
        aWithOffset.x += static_cast<int>(aOffset.x);
        aWithOffset.y += static_cast<int>(aOffset.y);
        
        const auto map = world->GetMap();
        std::vector<Solid*> allSolids;
        
        for (const auto layer : map->GetMapLayers())
        {
            if (layer->GetIsCollidable())
            {
                allSolids = layer->GetCollisionTiles();
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
            
            // Collision has occurred, now to determine the collision normal
            const auto dx = a->x + a->w / 2 - (result.x + result.w / 2);
            const auto dy = a->y + a->h / 2 - (result.y + result.h / 2);

            // Check if the collision is more horizontal or more vertical
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

        // no collision, so false and no normal are returned
        normal = vec2::Zero();
        return false; 
    }
}