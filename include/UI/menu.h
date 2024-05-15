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

/*
# WARNING:

EVERYTHING ABOUT MENU IS CURRENTLY A WIP WITH SPAGHETTI VARIABLE
COMPLETE MAKEOVER ARE VERY COMMON AT THIS STAGE OF DEVELOPMENT
BE AWARE
*/
class Menu
{
public:
    Menu();

    Input INPUT;

    ObjectSprite menuBGsprite = {0, 0, 20, 5};
    SDLTexture1D menuBGframe = CFG->loadTextures(
        "res/Menu/Background/", 64
    );

    bool finish = 0, end = 0;
    bool multi = 0;

    MenuButton button1P = {
        CFG->loadTexture("res/Menu/Button/P1.png")
    };
    MenuButton button2P = {
        CFG->loadTexture("res/Menu/Button/P2.png")
    };

    void update();
};

#endif