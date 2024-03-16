#ifndef NPC_DIALOGUE_H
#define NPC_DIALOGUE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <object2D.h>
#include <sprite.h>

class NpcDialogue : Object2D
{
private:
    // Dialogue bubble (no im not fucking using SDL ttf)
    SDL_Texture *bubble;
    SDL_Texture *npc;

public:
    NpcDialogue(float X = 0, float Y = 0, int w = 64, int h = 64, int hw = 64, int hh = 64, int sim = 0, int sfm = 0, int si = 0, int sf = 0, bool facing_player = true);
};

#endif