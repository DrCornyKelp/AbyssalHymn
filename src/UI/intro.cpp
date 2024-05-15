#include <UI/intro.h>

void IntroLogo::update()
{   
    // Draw in the dead center
    if (!fade_cur && !still) active = 0;
    if (!active) return;

    SDL_Rect desRect = {
        (CFG->WIDTH - w) / 2,
        (CFG->HEIGHT - h) / 2,
        w, h
    };

    if (appear) fade_cur ++;
    if (fade_cur >= fade_max) appear = 0;
    if (!appear && still) still --;
    if (!still && fade_cur) fade_cur --;

    int alpha = (fade_cur / fade_max) * 255;
    SDL_SetTextureAlphaMod(logo, alpha);
    SDL_RenderCopy(CFG->RENDERER, logo, NULL, &desRect);
}


void Intro::update()
{
    // INTRO SEQUENCE IS OVER, NO MORE
    if (finish) return;

    if (!logos.size())
    {
        CFG->TRANSIT_EFFECT.set(40, 100, 1);
        finish = 1;
        return;
    }

    // DRAWING THE LOGOS
    logos[0].update();

    if (!logos[0].active)
    {
        SDL_DestroyTexture(logos[0].logo);
        logos.erase(logos.begin());
    }
}