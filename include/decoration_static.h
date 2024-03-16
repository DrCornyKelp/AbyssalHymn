#ifndef DECORATION_STATIC_H
#define DECORATION_STATIC_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <tuple>

#include "game.h"
#include "sprite.h"

class DecorationStatic
{
private:
    int x;
    int y;
    int span_x;
    int span_y;
    // Drawing using screen cord
    // instead of relative player coord
    bool absolute;
    bool front = false;
    int alpha = 255;

    SDL_Texture *texture;
public:
    DecorationStatic(SDL_Renderer *renderer, const char *path, int dx, int dy, int sx, int sy, bool ab);

    void setAlpha(int a);
    void bringToFront();
    void draw(SDL_Renderer *renderer, int px, int py, bool focusX, int offsetX, bool focusY, int offsetY);
};

#endif