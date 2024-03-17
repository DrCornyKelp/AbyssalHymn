#ifndef DECORATION_H
#define DECORATION_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <tuple>

#include "game.h"
#include "object2D.h"
#include "sprite.h"

class Decoration
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

    const char *decor_path;

    SDL_Texture *texture;
public:
    Decoration(const char *dPath, int dx, int dy, int sx, int sy, bool ab);

    void initDecoration(SDL_Renderer *renderer, const char *path);
    void setAlpha(int a);
    void bringToFront();
    void draw(SDL_Renderer *renderer, int px, int py, bool focusX, int offsetX, bool focusY, int offsetY);
};

#endif