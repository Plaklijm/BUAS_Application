#include "Actor.h"

#include "BoxCollider.h"
#include "Collision.h"

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}
namespace Tmpl8
{
    Actor::Actor(vec2 position, vec2 size, World* world) : world(world), position(position), hitBox(new BoxCollider(position, size))
    {
    }

    // Ill explain the guts in this function, but the same applies to the MoveY function
    void Actor::MoveX(float amount)
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
                // check if the next pixel is free to move at
                if (!Collision::RectIntersectAt(&hitBox->GetHitBox(), vec2(sign, 0),collisionNormal, world))
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
                // check if the next pixel is free to move at
                if (!Collision::RectIntersectAt(&hitBox->GetHitBox(), vec2(0, sign),collisionNormal, world))
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
                    //printf("%f,%f", normal.x, normal.y);
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
}