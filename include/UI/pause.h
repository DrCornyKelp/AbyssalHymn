#ifndef PAUSE_H
#define PAUSE_H

#include <world.h>

class Pause
{
public:
    World *WORLD;

    SDL_Texture *lmao = CFG->loadTexture("res/");

    Pause(World *world);

    void update();
};

#endif