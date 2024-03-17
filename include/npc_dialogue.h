#ifndef NPC_DIALOGUE_H
#define NPC_DIALOGUE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <game.h>
#include <object2D.h>
#include <sprite.h>

class NpcDialogue : Object2D
{
private:
    // Dialogue bubble (no im not fucking using SDL ttf)
    const char *npc_path;
    const char *bubble_path;
    Sprite *bubble;
    Sprite *npc;

    bool display_bubble = false;
    bool facing_player;
    int alpha_cur = 0;
    int alpha_max;

    int sprite_width, sprite_height;
    int bubble_width, bubble_height;

public:
    NpcDialogue(const char* nPath, const char* bPath, float nx = 0, float ny = 0, int w = 128, int h = 128, int hw = 64, int hh = 64, int bw = 128, int bh = 32, int sw = 32, int sh = 32, int sim = 0, int sfm = 0, int si = 0, int sf = 0, int alpm = 180, bool f_player = true);

    void initNpc(SDL_Renderer *renderer);

    void setDisplay(bool display);
    void drawNpc(SDL_Renderer *renderer, int px, int py, bool focusX, int offsetX, bool focusY, int offsetY);
};

#endif