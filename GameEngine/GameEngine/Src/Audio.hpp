#ifndef Audio_hpp
#define Audio_hpp
#include "SDL.h"

class Audio {
public:
    ~Audio();
    void load(const char* filename);
    void play();
    void setVolume(int volume);

private:
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8* wavBuffer;
    SDL_AudioDeviceID deviceId;
    int volume = 2;
};

#endif /* Audio_hpp */