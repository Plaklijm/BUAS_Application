#include "Sound.h"

Sound::Sound(const std::string& filePath)
{
    // Load the sound
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
    // Add it to the queue and play it 
    SDL_QueueAudio(device, waveStart, waveLength);
    // Calling PauseAudioDevice to play seems very counterintuitive :o
    SDL_PauseAudioDevice(device, 0);
}

void Sound::StopSound(const SDL_AudioDeviceID device)
{
    SDL_PauseAudioDevice(device, 1);
}
