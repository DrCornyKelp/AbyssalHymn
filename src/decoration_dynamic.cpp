#include "decoration_dynamic.h"

DecorationDynamic::DecorationDynamic(SDL_Renderer *renderer, const char *path, int dx, int dy, int sw, int sh, int m_frame, int m_index, int scl, bool ab)
{
    texture = Sprite::loadTexture(renderer, path);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    x = dx; y = dy; scale = scl;
    sprite_width = sw; sprite_height = sh;
    sprite_max_index = m_index;
    sprite_max_frame = m_frame;
    absolute = ab;
};

void DecorationDynamic::setAlpha(int a)
{
    alpha = a;
    SDL_SetTextureAlphaMod(texture, a);
}
void DecorationDynamic::bringToFront()
{
    front = true;
}
void DecorationDynamic::draw(SDL_Renderer *renderer, int px, int py, bool focusX, int offsetX, bool focusY, int offsetY)
{   
    if (sprite_frame < sprite_max_frame)
        sprite_frame++;
    else {
        sprite_frame = 0;
        sprite_index++;
    }
    if (sprite_index >= sprite_max_index) sprite_index = 0;
    
    int rel_x = focusX ? offsetX + x - px : x;
    int rel_y = focusY ? offsetY + y - py : y;
    // Where to draw
    SDL_Rect desRect;
    if (absolute) desRect = {x, y, sprite_width * scale, sprite_height * scale};
    else desRect = {rel_x - sprite_width * scale / 2, Game::HEIGHT - rel_y - sprite_width * scale / 2, sprite_width * scale, sprite_height * scale};
    // Which sprite
    SDL_Rect srcRect = {sprite_width * sprite_index, 0, sprite_width, sprite_height};

    SDL_RenderCopy(renderer, texture, &srcRect, &desRect);
}