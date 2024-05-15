#ifndef INTRO_H
#define INTRO_H

#include <object2D.h>

#define IntroLogo1D std::vector<IntroLogo>

struct IntroLogo
{
    // Params
    SDL_Texture *logo;
    int w, h;
    float fade_max = 100;
    int still = 100;
    // Custom Value
    bool finish = 0;
    bool appear = 1;
    float fade_cur = 0;

    void update();
};

class Intro
{
public:
    IntroLogo1D logos = {
        {Object2D::loadTexture("res/IntroLogo/Valve.png"), 339, 100},
        {Object2D::loadTexture("res/IntroLogo/Riot.png"), 328, 200}
    };

    bool finish = 0;
    int BlackAlpha = 255;
    SDL_Texture *BlackScreen = Object2D::loadTexture("res/BlackScreen.png");

    void update();
};

#endif