#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SFML/Audio.hpp>

#include <algorithm>
#include <random>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <math.h>
#include <cmath>
#include <vector>
#include <tuple>
#include <map>

#define int1D std::vector<int>
#define int2D std::vector<int1D>

#define float1D std::vector<float>
#define float2D std::vector<float1D>

#define long1D std::vector<long>
#define long2D std::vector<long1D>

#define bool1D std::vector<bool>
#define bool2D std::vector<bool1D>

#define string0D std::string
#define string1D std::vector<string0D>
#define string2D std::vector<string1D>

#define SDLTexture1D std::vector<SDL_Texture*>
#define SDLTexture2D std::vector<SDLTexture1D>

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

    // TIMER
    long TIME = 0;

    // WINDOW/RENDERER
    SDL_Window *WINDOW = SDL_CreateWindow("Abyssal Hymn", SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *RENDERER = SDL_CreateRenderer(WINDOW, -1, 0);

    // DEBUG LOGGING
    string0D PRELOG = "";
    string0D DEVLOG = "";

    // Method
    void addDevlog(string0D text, int colorCode);
    void printDevlog();

    void resizeWindow(int W, int H);
    void frameHandler(int dlt);
    void drawIcon();

    // Some manipulation with string and vector

    string1D convertStrVec(string0D file_dir);

    int2D resizeInt2D(int1D vec, int r, int c);
    float2D resizeFloat2D(float1D vec, int r, int c);

    int1D convertStrInt1D(string0D str, char delimiter = ',');
    float1D convertStrFloat1D(string0D str, char delimiter = ',');
    long1D convertStrLong1D(string0D str, char delimiter = ',');

    int1D convertFloat1DInt(float1D vec);
    int2D convertFloat2DInt(float2D vec);
};

extern Configuration *CFG;

#endif