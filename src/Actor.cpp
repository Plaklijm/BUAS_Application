#include "Actor.h"

#include <cmath>

#include "template.h"

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

// Ill explain the guts in this function, but the same applies to the MoveY function
void Actor::MoveX(float amount)
{
    // Actors dont have the concept of velocity, acceleration etc, so a movement amount is passed in

    // The movement amount is put into a collector variable
    xRemainder += amount;
    // Round the remainder so that we only move in pixels, everything else will be stored in the remainder to perform in the next frame
    int move = round(xRemainder);
    if (move != 0)
    {
        // subtract the amount we will move from the remainder
        xRemainder -= move;
        // sign the move variable 
        int sign = sgn(move);
        // Move the actor
        while (move != 0)
        {
                // move the actor by 1 and remove it from the move, so when this hits 0 the amount we wanted to move is accomplished
                position.x += sign;
                move -= sign;
            /*if (!collideAt(solids, position + vec2(sign, 0)))
            {
            }
            else
            {
                if (onCollide != nullptr)
                {
                    onCollide();
                    break;
                }
            }*/
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
                position.y += sign;
                move -= sign;
            /*if (!collideAt(solids, position + vec2(0, sign)))
            {
            }
            else
            {
                if (onCollide != nullptr)
                {
                    onCollide();
                    break;
                }
            }*/
        }
    }
}
