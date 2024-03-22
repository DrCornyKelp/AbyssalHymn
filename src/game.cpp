#include "game.h"

// Setter

// void Game::setWindow(SDL_Window *win)
// {
//     window = win;
// }

// void Game::setRenderer(SDL_Renderer *rend)
// {
//     renderer = rend;
// }

// Getter
int Game::getWIDTH()
{
    return WIDTH;
}

int Game::getHEIGHT()
{
    return HEIGHT;
}

int Game::getFPS()
{
    return FPS;
}

int Game::getDELAYTIME()
{
    return DELAY_TIME;
}

SDL_Window *Game::getWindow()
{
    return window;
}

SDL_Renderer *Game::getRenderer()
{
    return renderer;
}

// Method
void Game::frameHandler(int dlt)
{
    Uint32 frame_start = SDL_GetTicks();
    Uint32 frame_duration = SDL_GetTicks() - frame_start;
    if (frame_duration < dlt)
    {
        SDL_Delay(dlt - frame_duration);
    }
}

void Game::drawIcon()
{
    SDL_SetWindowIcon(window, icon);
}