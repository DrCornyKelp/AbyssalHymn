#ifndef MENU_H
#define MENU_H

#include <world.h>

struct ButtonUI
{
    ObjectBox box;
    bool hold = 0, press = 0;

    SDL_Texture *bnormal,
                *bhover,
                *bpress;

    void update(Input *INPUT);
};

class Menu
{
public:
    Menu();

    Input INPUT;

    ObjectSprite sprite = {0, 0, 20, 5};
    SDLTexture1D menuBGframe = Object2D::loadTextures(
        "res/Menu/Background/", 64
    );

    void update();
};

#endif