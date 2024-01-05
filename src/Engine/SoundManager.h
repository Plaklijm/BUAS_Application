#pragma once
#include <map>
#include <memory>

#include "SDL2-2.28.5/include/SDL_audio.h"


// Sound manager using the built-in sound handling in SDL
// HANDLES ONLY FX SOUNDS, I tried to get it working with an workaround using an extra device etc, but there were a lot of
// bugs and nothing seemed to work, (also .wav music files are BIG)
// https://www.youtube.com/watch?v=hZ0TGCUcY2g&t=911s

// DISCLAIMER: I tried to use the SDL_Mixer library but i got errors regarding the DLL's. The fix was to put the DLL inside
// of the folder of the .exe but doing it this way i could only build for x64 (not the biggest issue but i wanted the compatibility)
// Also the SDL_Mixer library is the GO-TO choice when handling Audio in SDL, so for some parts of this class i needed to be a bit creative

enum SoundType
{
    s_CLICK = 0,
    s_WALK, 
    s_COLLECT,
    s_JUMP,
    s_DOUBLEJUMP,
    s_LEVELFINISH
};

class Sound;

class SoundManager
{
public:
    // Using a singleton because there will only be one SoundManager for the whole game
    static SoundManager* Instance();
    static void Release();

    void Cleanup() const;
    
    void PlaySound(SoundType id);
    void StopSound(SoundType id);
private:
    static SoundManager* instance;

    void SetupFX();
    SoundManager();
    ~SoundManager() = default;

    void SetupDevice();
    
    SDL_AudioDeviceID fxDevice;
    SDL_AudioSpec audioSpec;

    std::map<SoundType, Sound*> sounds;
};
