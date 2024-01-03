#include "PlayerInventory.h"

PlayerInventory::PlayerInventory()
{
    Reset();
}

void PlayerInventory::Reset()
{
    collected = 0;
}

void PlayerInventory::AddCollected()
{
    collected++;
}

bool PlayerInventory::HasCollectedAll(int amountNeeded) const
{
    if (collected >= amountNeeded)
        return true;

    return false;
}


