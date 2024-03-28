#include <decoration.h>
#include <player.h>

Decoration::Decoration(const char *dPath, float X, float Y, float w, float h,
                        int sw, int sh, int sim, int sfm , int si, int sf,
                        int grid, bool ab) :
    Object2D((X + w/2)*grid, (Y + h/2)*grid, w*grid, h*grid,
            0, 0, sw, sh, sim, sfm, si, sf),
    decor_path(dPath), absolute(ab)
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
    SDL_SetTextureAlphaMod(decor_texture, a);
}

void Decoration::initDecoration(SDL_Renderer *renderer)
{
    decor_texture = Sprite::loadTexture(renderer, decor_path);

    SDL_SetTextureBlendMode(decor_texture, SDL_BLENDMODE_BLEND);
    delete decor_path;
}

void Decoration::draw(SDL_Renderer *renderer, Player *player)
{
    // Only render if box is in sight
    if (!absolute && !background && Camera::objectOutBound(player, this))
        return;
    // Frame index shitty bang bang stuff handler
    objectSetSprite();

    // Draw
    SDL_Rect desRect;
    double cam_scale = player->getCameraScale();
    if (absolute || background)
        desRect = {int(getX() - getWidth() / 2), int(getY() - getHeight() / 2), getWidth(), getHeight()};
    else
        desRect =  {Camera::objectDrawX(player, this),
                    Camera::objectDrawY(player, this),
                    int(getWidth() * cam_scale),
                    int(getHeight() * cam_scale)};

    SDL_Rect srcRect = {getSprIndex() * getSprWidth(), 0, getSprWidth(), getSprHeight()};

    SDL_RenderCopy(renderer, decor_texture, (getSprIndexMax() > 0 ? &srcRect : NULL), &desRect);
}