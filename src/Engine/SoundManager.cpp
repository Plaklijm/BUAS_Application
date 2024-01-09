#include "SoundManager.h"

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

void SoundManager::Cleanup() const
{
    SDL_CloseAudioDevice(fxDevice);
}

SoundManager::SoundManager()
{
    SetupDevice();
    SetupFX();
}

void SoundManager::SetupDevice()
{
    // Create spec-sheet
    SDL_zero(audioSpec);
    audioSpec.freq = 44100;
    audioSpec.format = AUDIO_S16;
    audioSpec.channels = 2;
    audioSpec.samples = 4096;

    // Open channel
    fxDevice = SDL_OpenAudioDevice(nullptr, 0, &audioSpec, nullptr, 0);
    if (fxDevice == 0)
        printf("FX device error: %s", SDL_GetError());
}

void SoundManager::SetupFX()
{
    // Load all the sounds we want to play in memory
    sounds.emplace(s_CLICK, new Sound("assets/ui/sounds/Select.wav"));
    sounds.emplace(s_WALK, new Sound("assets/player/sounds/Step.wav"));
    sounds.emplace(s_COLLECT, new Sound("assets/player/sounds/Collect.wav"));
    sounds.emplace(s_JUMP, new Sound("assets/player/sounds/Jump.wav"));
    sounds.emplace(s_DOUBLEJUMP, new Sound("assets/player/sounds/DoubleJump.wav"));
    sounds.emplace(s_LEVELFINISH, new Sound("assets/player/sounds/LevelEnd.wav"));
    sounds.emplace(s_DEATH, new Sound("assets/player/sounds/Death.wav"));
}

// These funcs do exactly what they say they do :)
void SoundManager::PlaySound(SoundType id)
{
    sounds[id]->PlaySound(fxDevice);
}

void SoundManager::StopSound(SoundType id)
{
    sounds[id]->StopSound(fxDevice);
}
