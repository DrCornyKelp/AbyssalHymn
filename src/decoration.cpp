#include "decoration.h"

Decoration::Decoration(const char *dPath, float X, float Y, float w, float h, int sw, int sh, int sim, int sfm , int si, int sf, int grid, bool ab) :
    Object2D((X + w/2)*grid, (Y + h/2)*grid, w*grid, h*grid, sw*grid, sh*grid, sim, sfm, si, sf),
    decor_path(dPath), absolute(ab),
    sprite_width(sw), sprite_height(sh)
{}

void Decoration::setAbs(bool ab)
{
    absolute = ab;
}

void Decoration::initDecoration(SDL_Renderer *renderer)
{
    decor_sprite = new Sprite(getWidth() * getSprIndexMax(), getHeight(), 1, decor_path);
    decor_sprite->setTexture(Sprite::loadTexture(renderer, decor_path));

    SDL_SetTextureBlendMode(decor_sprite->getTexture(), SDL_BLENDMODE_BLEND);
    delete decor_path;
}

void Decoration::setAlpha(int a)
{
    alpha = a;
    SDL_SetTextureAlphaMod(decor_sprite->getTexture(), a);
}

void Decoration::draw(SDL_Renderer *renderer, int px, int py, bool focusX, int offsetX, bool focusY, int offsetY)
{
    // Camera is a piece of shit
    int rel_x = focusX ? offsetX + getX() - px : getX();
    int rel_y = focusY ? offsetY + getY() - py : getY();

    // Frame index shitty bang bang stuff handler
    if (getSprFrame() < getSprFrameMax())
    {
        setSprFrame(getSprFrame() + 1);
    }
    else
    {
        setSprFrame(0);
        setSprIndex(getSprIndex() + 1);
    }

    if (getSprIndex() >= getSprIndexMax())
        setSprIndex(0);

    int colli_x = abs(px - getX());
    int colli_y = abs(py - getY());

    // Only render if box is in sight
    if (absolute || (
        colli_x - getWidth() / 2 < Game::WIDTH &&
        colli_y - getHeight() / 2 < Game::HEIGHT
    )){
        SDL_Rect desRect;
        if (absolute) 
            desRect = {int(getX() - getWidth() / 2), int(getY() - getHeight() / 2), getWidth(), getHeight()};
        else
            desRect = {rel_x - getWidth() / 2, Game::HEIGHT - rel_y - getHeight() / 2, getWidth(), getHeight()};
        SDL_Rect srcRect = {getSprIndex() * getHitWidth(), 0, getHitWidth(), getHitHeight()};

        SDL_RenderCopy(renderer, decor_sprite->getTexture(), (getSprIndexMax() > 0 ? &srcRect : NULL), &desRect);
    }
}