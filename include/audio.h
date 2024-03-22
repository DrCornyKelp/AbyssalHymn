#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Audio
{
private:
public:
    static void playBGM(const char *wavPath);
    static void playSFX(const char *wavPath);
};

#endif