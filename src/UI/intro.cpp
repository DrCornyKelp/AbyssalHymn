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

    std::cout << fade_cur << "\n";
}


void Intro::update()
{
    if (!logos.size()) return;

    logos[0].update();

    if (logos[0].finish)
    {
        SDL_DestroyTexture(logos[0].logo);
        logos.erase(logos.begin());
    }
}