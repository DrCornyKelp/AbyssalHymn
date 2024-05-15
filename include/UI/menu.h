#ifndef MENU_H
#define MENU_H

#include <world.h>

struct MenuButton
{
    SDL_Texture *texture;
    int hover_min = 180;

    int hover_alpha = 0;
    void update(bool hover, SDL_Rect rect);
};

class Menu
{
public:
    Menu();

    Input INPUT;

    ObjectSprite menuBGsprite = {0, 0, 20, 5};
    SDLTexture1D menuBGframe = CFG->loadTextures(
        "res/Menu/Background/", 64
    );

    bool finish = 0,end = 0;

    MenuButton buttonStart = {
        CFG->loadTexture("res/Menu/Button/Start.png")
    };

    void update();
};

#endif