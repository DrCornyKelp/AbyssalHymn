#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Game
{
private:
    int FPS = 100;
    int DELAY_TIME = 1000 / FPS;
    bool QUIT = false;

    SDL_Window *window = SDL_CreateWindow("Abyssal Hymn", SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface *icon = SDL_LoadBMP("res/icon.bmp");

public:
    static const int WIDTH = 1280, HEIGHT = 720;
    // Setter
    // void setWIDTH(int w);
    // void setHEIGHT(int h);
    // void setFPS(int fps);
    // void setDELAYTIME(int dt);
    // void setWindow(SDL_Window *win);
    // void setRenderer(SDL_Renderer *rend);

    // Getter
    int getWIDTH();
    int getHEIGHT();
    int getFPS();
    int getDELAYTIME();

    SDL_Window *getWindow();
    SDL_Renderer *getRenderer();
    void frameHandler(int dlt);

    // Method
    void drawIcon();
};

#endif