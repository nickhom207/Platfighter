#ifndef Audio_hpp
#define Audio_hpp
#include "SDL.h"
#include "SDL_mixer.h"

class Audio {
public:
    ~Audio();
    int loadSound(const char* filename);
    int loadMusic(const char* filename);
    int playSound(int s, int pan, int volume);
    int playMusic(int s, int volume);
    void stop();
    void setPan(int channel, int pan);
    int INIT_Mixer();
    void QUIT_Mixer();

private:
    int volume = 50;
    double pan = 0.0;
};

#endif /* Audio_hpp */