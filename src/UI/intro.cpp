#include <UI/intro.h>

void IntroLogo::update()
{   
    // Draw in the dead center
    if (!fade_cur && !still) finish = 1;
    if (finish) return;

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

    std::cout << alpha << "\n";
    SDL_SetTextureAlphaMod(logo, alpha);
    SDL_RenderCopy(CFG->RENDERER, logo, NULL, &desRect);
}


void Intro::update()
{
    // INTRO SEQUENCE IS OVER, NO MORE
    if (finish) return;

    // DRAWING A BLACK SCREEN
    SDL_RenderCopy(CFG->RENDERER, BlackScreen, NULL, NULL);
    // UPDATING THE BLACK SCREEN
    if (!logos.size())
    {
        BlackAlpha -= 5;

        if (BlackAlpha < 0)
        {
            SDL_DestroyTexture(BlackScreen);
            finish = 1;
            return;
        }

        SDL_SetTextureAlphaMod(BlackScreen, BlackAlpha);
        return;
    };

    // DRAWING THE LOGOS
    logos[0].update();

    if (logos[0].finish)
    {
        SDL_DestroyTexture(logos[0].logo);
        logos.erase(logos.begin());
    }
}