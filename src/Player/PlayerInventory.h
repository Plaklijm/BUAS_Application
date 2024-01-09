#pragma once

// Simple class that keeps track of the current items collected

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
