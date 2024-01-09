#include "Actor.h"

#include "Object.h"
#include "Collision.h"

Actor::Actor(Tmpl8::vec2 position, Tmpl8::vec2 size, World* world) : world(world), position(position),
                                                       hitBox(new BoxCollider(position, size))
{
}

// Ill explain the guts in this function, but the same applies to the MoveY function
void Actor::MoveX(float amount, bool ignoreObjects, const Actor* playerRef)
{
    // Actors dont have the concept of velocity, acceleration etc, so a movement amount is passed in
    // The movement amount is put into a collector variable, the fractional remainders get carried to the next frame
    xRemainder += amount;
    
    // Round the remainder so that we only move in pixels, everything else will be stored in the remainder to perform in the next frame
    int move = round(xRemainder);
    if (move != 0)
    {
        // subtract the amount we will move from the remainder
        xRemainder -= move;
        // sign the move variable 
        const auto sign = Tmpl8::sgn(move);
        // Move the actor
        while (move != 0)
        {
            // If we need to ignore the objects in the scene (only implemented for the pushable objects (this could be a lot neater)) 
            if (!ignoreObjects)
            {
                const auto obj = Collision::RectIntersectObjects(&hitBox->GetHitBox(), Tmpl8::vec2(sign, 0), collisionNormalX, world);
                if (obj != nullptr && obj->GetType() == PUSHABLE)
                {
                    OnCollideX();
                    break;
                }
            }
            // Same here but then if we need to ignore the player or not
            if (playerRef != nullptr)
            {
                if (Collision::RectIntersectAt(&hitBox->GetHitBox(), Tmpl8::vec2(sign, 0), &playerRef->GetCollider()->GetHitBox(), collisionNormalX))
                {
                    OnCollideX();
                    break;
                }
            }
            // check if the next pixel is free to move at with the isPushing (only need to check the isPushing in the X direction)
            if (!Collision::RectIntersectAt(&hitBox->GetHitBox(), Tmpl8::vec2(sign, 0),collisionNormalX, world))
            {
                // There is no solid in the way that would prevent us from moving there.
                // move the actor by 1 and remove it from the move, so when this hits 0 the amount we wanted to move is accomplished
                position.x += sign;
                move -= sign;
                hitBox->SetPosition(position);
            }
            // the next pixel is a solid so we halt the movement
            else
            {
                OnCollideX();
                break;
            }
        }
    }
}

// Bit simpler version of the MoveX function
void Actor::MoveY(float amount)
{
    yRemainder += amount;
    int move = round(yRemainder);
    if (move != 0)
    {
        yRemainder -= move;
        int sign = Tmpl8::sgn(move);
        while (move != 0)
        {
            const auto obj = Collision::RectIntersectObjects(&hitBox->GetHitBox(), Tmpl8::vec2(0, sign), collisionNormalY, world);
            if (obj != nullptr && obj->GetType() == PUSHABLE)
            {
                OnCollideY();
                break;
            }
            if (!Collision::RectIntersectAt(&hitBox->GetHitBox(), Tmpl8::vec2(0, sign),collisionNormalY, world))
            {
                position.y += sign;
                move -= sign;
                hitBox->SetPosition(position);
            }
            else
            {
                OnCollideY();
                break;
            }
        }
    }
}

// Collision events
void Actor::OnCollideX()
{
    xRemainder = 0;
}

void Actor::OnCollideY()
{
    yRemainder = 0;
}