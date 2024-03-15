#include "audio.h"

void Audio::playBGM(const char *wavPath)
{
    // 22050, 44100, or 48000
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Music *music = Mix_LoadMUS(wavPath);
    Mix_PlayMusic(music, -1);
}

void Audio::playSFX(const char *wavPath)
{

}