#ifndef PARTICLE_EFFECT_H
#define PARTICLE_EFFECT_H

#include <object2D.h>

class Player;
class ParticleEffect : public Object2D
{
private:
    bool is_gone = false;
    bool can_repeat = false;

    SDL_Texture *pe_texture;

public:
    ParticleEffect( SDL_Texture *peTxture,
                    float X, float Y, int w, int h, // Position/Size in game
                    int sw, int sh, int sim, int sfm, // Animation properties
                    bool repeat);
    bool getIsGone();

    void draw(SDL_Renderer *renderer, Player *player);
};

#endif