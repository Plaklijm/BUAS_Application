﻿#include "Actor.h"

#include "Object.h"

Actor::Actor(vec2 position, vec2 size, World* world) : world(world), position(position),
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
        const auto sign = sgn(move);
        // Move the actor
        while (move != 0)
        {
            if (!ignoreObjects)
            {
                const auto obj = Collision::RectIntersectObjects(&hitBox->GetHitBox(), vec2(sign, 0), collisionNormalX, world);
                if (obj != nullptr && obj->GetType() == PUSHABLE)
                {
                    OnCollideX();
                    break;
                }
            }
            if (playerRef != nullptr)
            {
                if (Collision::RectIntersectAt(&hitBox->GetHitBox(), vec2(sign, 0), &playerRef->GetCollider()->GetHitBox(), collisionNormalX))
                {
                    OnCollideX();
                    break;
                }
            }
            // check if the next pixel is free to move at with the isPushing (only need to check the isPushing in the X direction)
            if (!Collision::RectIntersectAt(&hitBox->GetHitBox(), vec2(sign, 0),collisionNormalX, world))
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

void Actor::MoveY(float amount)
{
    yRemainder += amount;
    int move = round(yRemainder);
    if (move != 0)
    {
        yRemainder -= move;
        int sign = sgn(move);
        while (move != 0)
        {
            const auto obj = Collision::RectIntersectObjects(&hitBox->GetHitBox(), vec2(0, sign), collisionNormalY, world);
            if (obj != nullptr && obj->GetType() == PUSHABLE)
            {
                OnCollideY();
                break;
            }
            // check if the next pixel is free to move at
            if (!Collision::RectIntersectAt(&hitBox->GetHitBox(), vec2(0, sign),collisionNormalY, world))
            {
                // There is no solid in the way that would prevent us from moving there.
                // move the actor by 1 and remove it from the move, so when this hits 0 the amount we wanted to move is accomplished
                position.y += sign;
                move -= sign;
                hitBox->SetPosition(position);
            }
            // the next pixel is a solid so we halt the movement
            else
            {
                OnCollideY();
                break;
            }
        }
    }
}


void Actor::OnCollideX()
{
    xRemainder = 0;
}

void Actor::OnCollideY()
{
    yRemainder = 0;
}