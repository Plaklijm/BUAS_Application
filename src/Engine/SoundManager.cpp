#include "SoundManager.h"

#include <cstdio>

#include "Sound.h"

SoundManager* SoundManager::instance = nullptr;

SoundManager* SoundManager::Instance()
{
    if (!instance)
        instance = new SoundManager();

    return instance;
}

void SoundManager::Release()
{
    delete instance;
    instance = nullptr;
}

SoundManager::SoundManager()
{
    SetupDevice();
}

void SoundManager::SetupDevice()
{
    SDL_zero(audioSpec);
    audioSpec.freq = 44100;
    audioSpec.format = AUDIO_S16;
    audioSpec.channels = 2;
    audioSpec. samples = 4096;
    
    device = SDL_OpenAudioDevice(nullptr, 0, &audioSpec, nullptr, 0);
    if (device == 0)
    {
        printf("Sound device error: %s", SDL_GetError());
    }
}

Sound* testSound = new Sound("assets/player/sounds/Retro10.wav");
Sound* testSoundMusic = new Sound("assets/stranger-things-124008.wav");
void SoundManager::PlaySound(int id) const
{
    if (id == 1)
    {
        testSound->PlaySound(device);
    }
    else
    {
        testSoundMusic->PlaySound(device);
    }
    
}

void SoundManager::StopSound(int id) const
{
    if (id == 1)
    {
        testSound->StopSound(device);
    }
    else
    {
        testSoundMusic->StopSound(device);
    }
}
