#ifndef MENU_H
#define MENU_H

#include <world.h>

class Menu
{
public:
    Decoration *menuBG = new Decoration("res/Menu/Background/", 0, 0, CFG->WIDTH, CFG->HEIGHT, 1);
};

#endif