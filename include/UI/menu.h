#ifndef MENU_H
#define MENU_H

#include <world.h>

class Menu
{
public:
    Menu();

    Input INPUT;

    ObjectSprite sprite = {0, 0, 64, 10};
    SDLTexture1D menuBGframe = Object2D::loadTextures(
        "res/Menu/Background/", 64
    );

    void update();
};

#endif