#include "decoration.h"

Decoration::Decoration(const char *dPath, int dx, int dy, int sx, int sy, bool ab) :
x(dx), y(dy), span_x(sx), span_y(sy), absolute(ab)
{}

void Decoration::initDecoration(SDL_Renderer *renderer, const char *path)
{
    SDL_Texture *texture = Sprite::loadTexture(renderer, path);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    delete path;
}

void Decoration::setAlpha(int a)
{
    alpha = a;
    SDL_SetTextureAlphaMod(texture, a);
}
void Decoration::bringToFront()
{
    front = true;
}
void Decoration::draw(SDL_Renderer *renderer, int px, int py, bool focusX, int offsetX, bool focusY, int offsetY)
{
    int rel_x = focusX ? offsetX + x - px : x;
    int rel_y = focusY ? offsetY + y - py : y;

    SDL_Rect desRect;
    if (absolute) desRect = {x, y, span_x, span_y};
    else desRect = {rel_x - span_x / 2, Game::HEIGHT - rel_y - span_y / 2, span_x, span_y};

    SDL_RenderCopy(renderer, texture, NULL, &desRect);
}