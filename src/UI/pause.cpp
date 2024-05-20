#include <UI/pause.h>

Pause::Pause(World *world) :
    WORLD(world)
{}


void Pause::update()
{
    // Turn Off Audio
    WORLD->AUDIO->setPlistVolMax(0);
    WORLD->AUDIO->updateTrack();

    CFG->drawFullscreen(WORLD->MapCur->MapInfo.pause_bg, 1);

    SDL_RenderCopy(CFG->RENDERER, WORLD->MapCur->MapInfo.pause_bg, NULL, NULL);
}