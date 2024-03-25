#include <decoration.h>
#include <player.h>

Decoration::Decoration(const char *dPath, float X, float Y, float w, float h, int sw, int sh, int sim, int sfm , int si, int sf, int grid, bool ab) :
    Object2D((X + w/2)*grid, (Y + h/2)*grid, w*grid, h*grid,
            sw, sh, sim, sfm, si, sf),
    decor_path(dPath), absolute(ab),
    sprite_width(sw), sprite_height(sh)
{}

void Decoration::setAbs(bool ab)
{
    absolute = ab;
}
void Decoration::setBackground(bool bg)
{
    background = bg;
}
void Decoration::setAlpha(int a)
{
    alpha = a;
    SDL_SetTextureAlphaMod(decor_sprite->getTexture(), a);
}

void Decoration::initDecoration(SDL_Renderer *renderer)
{
    decor_sprite = new Sprite(getWidth() * getSprIndexMax(), getHeight(), 1, decor_path);
    decor_sprite->setTexture(Sprite::loadTexture(renderer, decor_path));

    SDL_SetTextureBlendMode(decor_sprite->getTexture(), SDL_BLENDMODE_BLEND);
    delete decor_path;
}

void Decoration::draw(SDL_Renderer *renderer, Player *player)
{
    // Only render if box is in sight
    if (!absolute && !background && Camera::objectOutBound(player, this))
        return;
    // Frame index shitty bang bang stuff handler
    Camera::objectSetSprite(this);

    // Draw
    SDL_Rect desRect;
    double cam_scale = player->getCameraScale();
    if (absolute || background)
        desRect = {int(getX() - getWidth() / 2), int(getY() - getHeight() / 2), getWidth(), getHeight()};
    else
        desRect =  {Camera::objectDrawX(player, this),
                    Camera::objectDrawY(player, this),
                    int(getWidth() * cam_scale), int(getHeight() * cam_scale)};

    SDL_Rect srcRect = {getSprIndex() * getHitWidth(), 0, getHitWidth(), getHitHeight()};

    SDL_RenderCopy(renderer, decor_sprite->getTexture(), (getSprIndexMax() > 0 ? &srcRect : NULL), &desRect);
}