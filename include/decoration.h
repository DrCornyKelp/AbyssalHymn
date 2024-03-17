#ifndef DECORATION_H
#define DECORATION_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <tuple>

#include "game.h"
#include "object2D.h"
#include "sprite.h"

class Decoration : Object2D
{
private:
    bool absolute;
    bool full_screen;
    int alpha = 255;

    const char *decor_path;

    Sprite *decor_sprite;

    int sprite_width;
    int sprite_height;
public:
    Decoration(const char *dPath = "", float X = 0, float Y = 0, float w = 0, float h = 0, int sw = 0, int sh = 0, int sim = 0, int sfm = 0, int si = 0, int sf = 0, int grid = 1, bool ab = false);

    void setAbs(bool ab);
    void setAlpha(int a);
    void initDecoration(SDL_Renderer *renderer);
    void draw(SDL_Renderer *renderer, int px, int py, bool focusX, int offsetX, bool focusY, int offsetY);
};

#endif