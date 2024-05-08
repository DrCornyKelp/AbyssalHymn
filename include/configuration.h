#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Configuration
{
public:
    Configuration();

    // GAMESTATE
    bool QUIT = 0;
    SDL_Surface *ICON = SDL_LoadBMP("res/icon.bmp");

    // FPS
    int FPS = 100;
    int DELAY_TIME = 10;

    // WINDOW SIZE
    // int WIDTH = 1536, HEIGHT = 896;
    int WIDTH = 1280, HEIGHT = 768;

    // WINDOW/RENDERER
    SDL_Window *WINDOW = SDL_CreateWindow("Abyssal Hymn", SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *RENDERER = SDL_CreateRenderer(WINDOW, -1, 0);

    // DEBUG LOGGING
    std::string PRELOG = "";
    std::string DEVLOG = "";

    // Method
    void addDevlog(std::string text, int colorCode);
    void printDevlog();

    void resizeWindow(int W, int H);
    void frameHandler(int dlt);
    void drawIcon();
};

extern Configuration *CFG;

#endif