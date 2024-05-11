#include <configuration.h>

Configuration *CFG = new Configuration();

// CONSTRUCTOR
Configuration::Configuration() {};

// METHOD

void Configuration::addDevlog(string0D text, int colorCode)
{ DEVLOG += "| \033[" + std::to_string(colorCode) + "m" + text + "\033[0m "; }
void Configuration::printDevlog()
{
    if (DEVLOG == "" || DEVLOG == PRELOG) return;
    PRELOG = DEVLOG;
    std::cout << DEVLOG << "\n";
}

void Configuration::resizeWindow(int W, int H)
{
    WIDTH = W; HEIGHT = H;
    SDL_SetWindowSize(WINDOW, W, H);
}

void Configuration::frameHandler(int dlt)
{
    Uint32 frame_start = SDL_GetTicks();
    Uint32 frame_duration = SDL_GetTicks() - frame_start;
    if (frame_duration < dlt)
        SDL_Delay(dlt - frame_duration);
}

void Configuration::drawIcon()
{ SDL_SetWindowIcon(WINDOW, ICON); }