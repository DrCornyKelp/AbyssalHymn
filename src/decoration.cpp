#include "decoration.h"

Decoration::Decoration(const char *dPath, float X, float Y, float w, float h, int sw, int sh, int sim, int sfm , int si, int sf, int grid, bool ab) :
    Object2D((X + w/2)*grid, (Y + w/2)*grid, w*grid, h*grid, w*grid, h*grid, sim, sfm, sf, si), decor_path(dPath), absolute(ab)
{
    std::cout << dPath << " " << getWidth() << " " << getHeight() << "\n";
}

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
    SDL_SetTextureAlphaMod(decor_sprite->getTexture(), 100);
}

void Decoration::draw(SDL_Renderer *renderer, int px, int py, bool focusX, int offsetX, bool focusY, int offsetY)
{
    // Camera is a piece of shit
    int rel_x = focusX ? offsetX + getX() - px : getX();
    int rel_y = focusY ? offsetY + getY() - py : getY();

    // Frame index shitty bang bang stuff handler
    if (getSprFrame() < getSprFrameMax())
        setSprFrame(getSprFrame() + 1);
    else
    {
        setSprFrame(0);
        setSprIndex(getSprIndex() + 1);
    }

    if (getSprIndex() >= getSprIndexMax())
        setSprIndex(0);

    SDL_Rect desRect;
    if (absolute) desRect = {int(getX()), int(getY()), getWidth(), getHeight()};
    else desRect = {rel_x - getWidth() / 2, Game::HEIGHT - rel_y - getHeight() / 2, getWidth(), getHeight()};

    SDL_RenderCopy(renderer, decor_sprite->getTexture(), NULL, &desRect);
}