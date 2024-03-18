#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Sprite
{
private:
    int sprite_width;
    int sprite_height;
    int display_ratio;

    const char *sprite_path;

    SDL_Texture *spriteTexture;

public:
    Sprite(int sw, int sh, float dr, const char *spritePath);

    void setSpritePath(const char *sp);
    const char *getSpritePath();

    void setTexture(SDL_Texture *texture);
    SDL_Texture *getTexture();

    static SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *spritePath);
};

#endif