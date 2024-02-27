#include "Audio.hpp"

Audio::~Audio() {
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
    SDL_MixAudioFormat(wavBuffer, nullptr, AUDIO_S16SYS, wavLength, volume);
}

void Audio::load(const char* filename) {
    SDL_LoadWAV(filename, &wavSpec, &wavBuffer, &wavLength);
    deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}

void Audio::play() {
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
}

void Audio::setVolume(int volume) {
    if (volume < 0) {
        volume = 0;
    }
    else if (volume > SDL_MIX_MAXVOLUME) {
        volume = SDL_MIX_MAXVOLUME;
    }
    SDL_MixAudioFormat(wavBuffer, nullptr, AUDIO_S16SYS, wavLength, volume);
}