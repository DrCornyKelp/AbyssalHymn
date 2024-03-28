#include <particle_effect.h>
#include <player.h>

ParticleEffect::ParticleEffect(
    SDL_Texture *peTxture,
    float X, float Y, int w, int h, // Position/Size in game
    int sw, int sh, int sim, int sfm, // Animation properties
    bool repeat) :
    Object2D(X, Y, w, h, 0, 0,
            sw, sh, sim, sfm, 0, 0),
    pe_texture(peTxture),
    can_repeat(repeat)
{}
bool ParticleEffect::getIsGone() { return is_gone; }

void ParticleEffect::draw(SDL_Renderer *renderer, Player *player)
{
    // Outside seeable? unrender
    if (Camera::objectOutBound(player, this))
        return;
    // Frame index shitty bang bang stuff handler
    if (!can_repeat && getSprIndex() == getSprIndexMax())
        is_gone = true;
    objectSetSprite();

    // Draw
    double cam_scale = player->getCameraScale();
    SDL_Rect desRect = {Camera::objectDrawX(player, this),
                        Camera::objectDrawY(player, this),
                        int(getWidth() * cam_scale),
                        int(getHeight() * cam_scale)};
    
    SDL_Rect srcRect = {getSprIndex() * getSprWidth(), 0, getSprWidth(), getSprHeight()};
}