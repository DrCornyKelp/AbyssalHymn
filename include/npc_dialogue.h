#ifndef NPC_DIALOGUE_H
#define NPC_DIALOGUE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <game.h>
#include <object2D.h>
#include <sprite.h>

class Player;
class NpcDialogue : Object2D
{
private:
    // Dialogue bubble (no im not fucking using SDL ttf)
    const char *npc_path;
    const char *bubble_path;
    SDL_Texture *bubble_texture;
    SDL_Texture *npc_texture;

    bool display_bubble = false;
    int alpha_cur = 0;
    int alpha_max;

    int bubble_width, bubble_height;

public:
    NpcDialogue(const char* nPath, const char* bPath, float nx = 0, float ny = 0, int w = 0, int h = 0,
                int hw = 0, int hh = 0, int bw = 0, int bh = 0, int sw = 0, int sh = 0,
                int sim = 0, int sfm = 0, int alpm = 200, int grid = 64);

    void initNpc(SDL_Renderer *renderer);

    void setDisplay(bool display);
    void draw(SDL_Renderer *renderer, Player *player);
};

#endif