#ifndef Audio_hpp
#define Audio_hpp
#include "SDL.h"
#include "SDL_mixer.h"

class Audio {
public:
    ~Audio();
    int loadSound(const char* filename);
    int loadMusic(const char* filename);
    int playSound(int s, int pan);
    int playMusic(int s);
    void stop();
    void setVolume(int volume);
    void setPan(int channel, int pan);
    int INIT_Mixer();
    void QUIT_Mixer();

private:
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8* wavBuffer;
    SDL_AudioDeviceID deviceId;
    int volume = 30;
    double pan = 0.0;
};

#endif /* Audio_hpp */