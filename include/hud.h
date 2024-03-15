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

    // Hud texture
    SDL_Texture *airbornTexture;
    int airbornDisplay = 300;

    // const char *fontpath = "res/Font/Ultrakill.ttf";
    // TTF_Font *fonthud = TTF_OpenFont(fontpath, 24);
public:
    Hud(SDL_Renderer *renderer, Player *p);

    // Setter
    void setAlpha(int a);
    // No Getter

    // Alot of drawing
    void drawHealth(SDL_Renderer *renderer);
    void drawAirborne(SDL_Renderer *renderer);
    void draw(SDL_Renderer *renderer);
};

#endif