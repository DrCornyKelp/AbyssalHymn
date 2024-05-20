#ifndef PAUSE_H
#define PAUSE_H

#include <world.h>

class Pause
{
public:
    World *WORLD;
    bool end_pause = 1;

    float transit_time = 0;
    float transit_max = 20;

    SDL_Texture *lmao = CFG->loadTexture("res/");

    Pause(World *world);

    void update(Input *input);
    float transit_ratio(bool reverse = 0);
};

#endif