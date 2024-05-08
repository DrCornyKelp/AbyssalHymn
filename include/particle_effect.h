#ifndef PARTICLE_EFFECT_H
#define PARTICLE_EFFECT_H

#include <object2D.h>

#define Particle1D std::vector<ParticleEffect*>

class Player;
class ParticleEffect : public Object2D
{
private:
    bool is_gone = false;
    bool can_repeat = false;

    SDL_Texture *pe_texture;

public:
    ~ParticleEffect();
    ParticleEffect( SDL_Texture *peTxture,
                    float X, float Y, int w, int h, // Position/Size in game
                    int sw, int sh, int sim, int sfm, // Animation properties
                    bool repeat);
    ParticleEffect( SDL_Texture *peTxture,
                    float X, float Y, int w, int h, // Position/Size in game
                    int sw, int sh, int sim, int srm, int sfm, // Animation properties
                    bool repeat);
    bool getIsGone();

    void draw(Player *player);
};

#endif