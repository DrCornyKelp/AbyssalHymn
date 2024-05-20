#include <UI/pause.h>

Pause::Pause(World *world) :
    WORLD(world)
{}

void Pause::update(Input *input)
{
    // Turn Off Audio
    WORLD->AUDIO->setPlistVolMax(0);
    WORLD->AUDIO->updateTrack();

    if (!end_pause && transit_time < transit_max)
        transit_time ++;
    if (end_pause && transit_time > 0)
        transit_time --;
    if (end_pause && !transit_time)
        CFG->STATE = 1;

    if (input->escape.press())
    {
        input->escape.hold = 1;
        end_pause = 1;
    }

    // Draw And Stuff

    SDL_SetTextureAlphaMod(
        WORLD->MapCur->MapInfo.pause_bg, 255 * transit_ratio()
    );

    CFG->drawFullscreen(WORLD->MapCur->MapInfo.pause_bg, 1);
}

float Pause::transit_ratio(bool reverse)
{ 
    float rat = transit_time / transit_max;
    return reverse ? 1 - rat : rat;
}