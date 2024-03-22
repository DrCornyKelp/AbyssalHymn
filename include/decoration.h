#ifndef DECORATION_H
#define DECORATION_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <tuple>

#include "game.h"
#include "object2D.h"
#include "sprite.h"

class Player;
class Decoration : public Object2D
{
private:
    bool absolute = false;
    bool background = false;
    int alpha = 255;

    const char *decor_path;

    Sprite *decor_sprite;

    int sprite_width;
    int sprite_height;
public:
    // ==== NOTE!!! ====
    // position <x, y> is defined with grid (actual x = x * grid)
    // other value are calculated with original value
    Decoration(const char *dPath = "", float X = 0, float Y = 0, float w = 0, float h = 0, int sw = 0, int sh = 0, int sim = 0, int sfm = 0, int si = 0, int sf = 0, int grid = 64, bool ab = false);

    void setAbs(bool ab);
    void setBackground(bool bg);
    void setAlpha(int a);
    void initDecoration(SDL_Renderer *renderer);
    void draw(SDL_Renderer *renderer, Player *player);
};

#endif