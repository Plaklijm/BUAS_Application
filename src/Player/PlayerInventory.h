#pragma once

class PlayerInventory
{
public:
    PlayerInventory();
    
    void Reset();

    void AddCollected();
    
    bool HasCollectedAll(int amountNeeded) const;
private:
    int collected;
};
