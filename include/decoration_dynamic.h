#ifndef DECORATION_DYNAMIC_H
#define DECORATION_DYNAMIC_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sprite.h"

class DecorationDynamic
{
private:
    int x;
    int y;
    int sprite_width;
    int sprite_height;
    int scale;
    // Drawing using screen cord
    // instead of relative player coord 
    bool absolute;
    bool front = false;
    int alpha = 255;

    // Frame hanlder
    int sprite_index = 0;
    int sprite_max_index;
    int sprite_frame = 0;
    int sprite_max_frame;

    SDL_Texture *texture;
public:
    DecorationDynamic(SDL_Renderer *renderer, const char *path, int dx, int dy, int sw, int sh, int m_frame, int m_index, int scl, bool ab);

    void setAlpha(int a);
    void bringToFront();
    void draw(SDL_Renderer *renderer, int px, int py, bool focusX, int offsetX, bool focusY, int offsetY);
};

#endif