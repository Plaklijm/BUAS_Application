#pragma once
#include "SDL2-2.28.5/include/SDL_audio.h"

// Sound manager using the built-in sound handling in SDL
// I could've used SLD_Mixer (which is a bit more robust/simpler but i didn't want to install extra libraries when SDL already supports it)
// https://www.youtube.com/watch?v=hZ0TGCUcY2g&t=911s

class SoundManager
{
public:
    // Using a singleton because there will only be one SoundManager for the whole game
    static SoundManager* Instance();
    static void Release();

    void PlaySound(int id) const;
    void StopSound(int id) const;
private:
    static SoundManager* instance;

    SoundManager();
    ~SoundManager() = default;

    void SetupDevice();
    
    SDL_AudioDeviceID device;
    SDL_AudioSpec audioSpec;
};
