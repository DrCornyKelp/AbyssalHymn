#include <particle_effect.h>
#include <player.h>

ParticleEffect::~ParticleEffect()
{ SDL_DestroyTexture(pe_texture); }
ParticleEffect::ParticleEffect(
    SDL_Texture *peTxture,
    float X, float Y, int w, int h, // Box
    int sw, int sh, int sim, int sfm, // Sprite
    bool repeat) :
    Object2D(X, Y, w, h, 0, 0,
            sw, sh, sim, sfm, 0, 0),
    pe_texture(peTxture),
    can_repeat(repeat)
{}
ParticleEffect::ParticleEffect(
    SDL_Texture *peTxture,
    float X, float Y, int w, int h, // Box
    int sw, int sh, int sim, int srm, int sfm, // Sprite
    bool repeat) :
    Object2D(X, Y, w, h, 0, 0,
            sw, sh, sim, sfm, 0, 0),
    pe_texture(peTxture),
    can_repeat(repeat)
{ setSprRowMax(srm); }

bool ParticleEffect::getIsGone() { return is_gone; }

void ParticleEffect::draw(Player *player)
{
    // Outside seeable? unrender
    if (Camera::objectIgnore(player, this, true)) return;

    // Frame index shitty bang bang stuff handler
    // (more advanced than the other ig)
    if (objectSetSprite() && !can_repeat)
    { is_gone = true; return; }

    // Draw
    SDL_Rect desRect = {Camera::objectDrawX(player, this),
                        Camera::objectDrawY(player, this),
                        getWidth(), getHeight()};

    SDL_Rect srcRect = {getSprIndex() * getSprWidth(),
                        getSprRow() * getSprHeight(),
                        getSprWidth(), getSprHeight()};

    SDL_RenderCopy(CFG->RENDERER, pe_texture, &srcRect, &desRect);
}