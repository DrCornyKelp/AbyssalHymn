#include "audio.h"

void Audio::playBGM(const char *wavPath)
{
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Music *music = Mix_LoadMUS(wavPath);
    Mix_PlayMusic(music, 0);
}

void Audio::playSFX(const char *wavPath)
{

}