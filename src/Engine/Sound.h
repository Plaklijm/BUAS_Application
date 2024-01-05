#pragma once
#include <SDL_audio.h>
#include <string>

class Sound
{
public:
    Sound(const std::string& filePath);
    ~Sound();
    
    void PlaySound(SDL_AudioDeviceID device) const;
    void StopSound(SDL_AudioDeviceID device);
    
private:
    // properties of the loaded Wav file 
    SDL_AudioSpec audioSpec;
    Uint8* waveStart;
    Uint32 waveLength;
};
