#pragma once

class GameState
{
    /**
     * This is the baseclass for the GameState. Every state inherits from this class
     * Made so that the game knows in which state its in and reacts accordingly. 
     */
public:
    enum StateCode
    {
        QUIT, CONTINUE, MAIN_MENU, GAME_START, GAME_OVER
    };

    virtual ~GameState() {};

    // State functions that each state must implement
    virtual void Load(int prevState = 0) = 0;
    virtual void UnLoad() = 0;
    virtual StateCode Update() = 0;
    virtual void Render() = 0;
};
