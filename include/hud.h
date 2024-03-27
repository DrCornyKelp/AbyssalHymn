#ifndef HUD_H
#define HUD_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// #include <SDL2/SDL_ttf.h>
#include <string>
#include <math.h>
#include <tuple>
#include <vector>

#include "player.h"
#include "sprite.h"

class Hud {
private:
    float alpha = 120; // Opacity

    Player* player;

    int bobbing = 0;
    int bobbing_direction = 1;

    int airbornDisplay = 300;

    // Hud texture
    SDL_Texture *airbornTexture;

    // Head Up texture
    SDL_Texture *combatReadyTexture;
    SDL_Texture *combatDelayTexture;
    SDL_Texture *combatChargeTexture;
    SDL_Texture *superJumpReadyTexture;
    SDL_Texture *invincibleTexture;
public:
    Hud(SDL_Renderer *renderer, Player *p);

    // Setter
    void setAlpha(int a);
    // No Getter

    // Alot of drawing
    void drawHealth(SDL_Renderer *renderer);
    void drawAirborne(SDL_Renderer *renderer);
    void drawHeadUpStat(SDL_Renderer *renderer);
    void draw(SDL_Renderer *renderer);
};

#endif