#include <UI/pause.h>

Pause::Pause(World *world) :
    WORLD(world)
{}


void Pause::update()
{
    WORLD->AUDIO->setPlistVolMax(0);
    WORLD->AUDIO->updateTrack();
}