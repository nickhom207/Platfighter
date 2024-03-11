#include "Audio.hpp"
#include <vector>
#include <iostream>

std::vector<Mix_Chunk*> sounds;
std::vector<Mix_Music*> music;

Audio::~Audio() {
    SDL_FreeWAV(wavBuffer);
    SDL_CloseAudioDevice(deviceId);
}

int Audio::loadSound(const char* filename) {
    Mix_Chunk* mchunk = NULL;
    mchunk = Mix_LoadWAV(filename);

    if (mchunk == NULL) {
        printf("Failed to load audio - SDL_Mixer error: %s\n", Mix_GetError());
        return -1;
    }

    sounds.push_back(mchunk);
    return sounds.size() - 1;
}

int Audio::loadMusic(const char* filename) {
    Mix_Music* m = NULL;
    m = Mix_LoadMUS(filename);
    if (m == NULL) {
        printf("Failed to load music - SDL_Mixer error: %s\n", Mix_GetError());
        return -1;
    }
    music.push_back(m);
    return music.size() - 1;
}

int Audio::playSound(int s, int pan) {
    int channel = Mix_PlayChannel(-1, sounds[s], 0);
    if (channel != -1) {
        Mix_Volume(channel, volume);
        setPan(channel, pan);
    }
    return channel;
}

int Audio::playMusic(int m) {
    if (Mix_PlayingMusic() == 0) {
        Mix_Volume(1, volume);
        Mix_PlayMusic(music[m], -1);
    }
    return 0;
}

void Audio::stop() {
    SDL_PauseAudioDevice(deviceId, 1);
}

int volume;
void Audio::setVolume(int v) {
    volume = (MIX_MAX_VOLUME * v) / 100;
}

void Audio::setPan(int channel, int pan) {
    if (pan > 100) {
        pan = 100;
    }
    else if (pan < -100) {
        pan = -100;
    }

    //-100 is left, 100 is right, 0 is middle
    int leftVolume = MIX_MAX_VOLUME;
    int rightVolume = MIX_MAX_VOLUME;

    if (pan < 0) {
        rightVolume = MIX_MAX_VOLUME + pan * MIX_MAX_VOLUME / 100;
    }
    else if (pan > 0) {
        leftVolume = MIX_MAX_VOLUME - pan * MIX_MAX_VOLUME / 100;
    }

    Mix_SetPanning(channel, leftVolume, rightVolume);
}


int Audio::INIT_Mixer() {
    Mix_Init(MIX_INIT_WAVPACK);
    SDL_Init(SDL_INIT_AUDIO);

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Failed to INIT SDL_Mixer - Err: %s\n", Mix_GetError());
        return -1;
    }

    setVolume(50);
    return 0;
}

void Audio::QUIT_Mixer() {
    for (int s = 0; s < sounds.size(); s++) {
        Mix_FreeChunk(sounds[s]);
        sounds[s] = NULL;
    }

    for (int s = 0; s < music.size(); s++) {
        Mix_FreeMusic(music[s]);
        music[s] = NULL;
    }
    Mix_Quit();
}