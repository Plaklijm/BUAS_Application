#include "Sound.h"

Sound::Sound(const std::string& filePath)
{
    if (SDL_LoadWAV(filePath.c_str(), &audioSpec, &waveStart, &waveLength) == nullptr)
    {
        printf("Failed loading wav file with name: %s", filePath.c_str());
    }
}

Sound::~Sound()
{
    SDL_FreeWAV(waveStart);
}

void Sound::PlaySound(const SDL_AudioDeviceID device) const
{
    SDL_QueueAudio(device, waveStart, waveLength);
    SDL_PauseAudioDevice(device, 0);
}

void Sound::StopSound(const SDL_AudioDeviceID device)
{
    SDL_PauseAudioDevice(device, 1);
}
