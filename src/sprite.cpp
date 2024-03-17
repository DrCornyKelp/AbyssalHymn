#include "sprite.h"

Sprite::Sprite(int sw, int sh, float dr, const char *sPath) :
    sprite_path(sPath),
    sprite_width(sw),
    sprite_height(sh),
    display_ratio(dr)
{}

void Sprite::setSpritePath(const char *sp)
{
    sprite_path = sp;
}

const char *Sprite::getSpritePath()
{
    return sprite_path;
}

void Sprite::setTexture(SDL_Texture *texture)
{
    spriteTexture = texture;
    delete sprite_path;
}

SDL_Texture *Sprite::getTexture()
{
    return spriteTexture;
}

SDL_Texture *Sprite::loadTexture(SDL_Renderer *renderer, const char *spritePath)
{
    SDL_Surface *surface = IMG_Load(spritePath);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    // Get rid of stupid old loaded surface
    SDL_FreeSurface(surface);

    return texture;
}