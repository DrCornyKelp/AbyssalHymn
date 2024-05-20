#ifndef PAUSE_H
#define PAUSE_H

#include <world.h>

class Pause
{
public:
    World *WORLD;
    float transit_time = 0;
    float transit_max = 100;

    SDL_Texture *lmao = CFG->loadTexture("res/");

    Pause(World *world);

    void update();
};

#endif