#ifndef PAUSE_H
#define PAUSE_H

#include <world.h>

class Pause
{
public:
    World *WORLD;

    Pause(World *world);

    void update();
};

#endif