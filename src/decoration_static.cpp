#include "decoration_static.h"

DecorationStatic::DecorationStatic(SDL_Renderer *renderer, const char *path, int dx, int dy, int sx, int sy, bool ab)
{
    texture = Sprite::loadTexture(renderer, path);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    x = dx; y = dy;
    span_x = sx; span_y = sy;
    absolute = ab;
};

void DecorationStatic::setAlpha(int a)
{
    alpha = a;
    SDL_SetTextureAlphaMod(texture, a);
}
void DecorationStatic::bringToFront()
{
    front = true;
}
void DecorationStatic::draw(SDL_Renderer *renderer, int px, int py, bool focusX, int offsetX, bool focusY, int offsetY)
{
    int rel_x = focusX ? offsetX + x - px : x;
    int rel_y = focusY ? offsetY + y - py : y;

    SDL_Rect desRect;
    if (absolute) desRect = {x, y, span_x, span_y};
    else desRect = {rel_x - span_x / 2, Game::HEIGHT - rel_y - span_y / 2, span_x, span_y};

    SDL_RenderCopy(renderer, texture, NULL, &desRect);
}