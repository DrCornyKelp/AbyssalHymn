#ifndef INTRO_H
#define INTRO_H

#include <object2D.h>

#define IntroLogo1D std::vector<IntroLogo>

struct IntroLogo
{
    // Params
    SDL_Texture *logo;
    int w, h;
    int fade_max = 100;
    int still = 100;
    // Custom Value
    bool finish = 0;
    bool appear = 1;
    int fade_cur = 0;
    int alpha = 0;

    void update();
};

class Intro
{
public:
    IntroLogo1D logos = {
        {Object2D::loadTexture("res"), 100, 100}
    };

    void update();
};

#endif