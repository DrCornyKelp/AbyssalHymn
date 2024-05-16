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

class Configuration;

struct TransitionEffect
{
    SDL_Texture *BLACKSCREEN;
    float side_max = 100;
    float mid_max = 100;
    float side_cur = 0;
    float mid_cur = 0;
    bool active = 0;
    bool fade = 0;

    void update();
    void set(float s, float m, bool skipStart = 0);
    // Brighten Black Screen
    bool leftactive();
    // Fading Black Screen
    bool rightactive();
    // Middle
    bool midpoint();
};

class Configuration
{
public:
    ~Configuration();
    Configuration();
    void postupdate();

    // GAMESTATE
    bool QUIT = 0;

    /*  STATE LIST
        0: Menu
        1: Playing
        2: Pause
    */
    short STATE = 0;
    void changeState();

    // TIME/FPS
    int FPS = 100;
    long RUNTIME = 0;
    long WORLDTIME = 0;
    int DELAY_TIME = 10;
    void frameHandler();

    // WINDOW SIZE
    // int WIDTH = 1536, HEIGHT = 896;
    int WIDTH = 1280, HEIGHT = 768;
    void resizeWindow(int W, int H);

    // WINDOW/RENDERER
    SDL_Window *WINDOW = SDL_CreateWindow("Abyssal Hymn", SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *RENDERER = SDL_CreateRenderer(WINDOW, -1, 0);
    SDL_Surface *ICON = SDL_LoadBMP("res/icon.bmp");
    // TEXTURE FUNCTIONS
    static SDL_Texture *loadTexture(string0D path);
    static SDLTexture1D loadTextures(string0D path, int max);

    // TRANSITION
    TransitionEffect TRANSIT_EFFECT;

    // DEBUG LOGGING
    string0D PRELOG = "";
    string0D DEVLOG = "";
    void addDevlog(string0D text, int colorCode);
    void printDevlog();
    static bool isComment(string0D str);

    // ====== Some manipulation with string and vector ======

    static string1D convertStrVec(string0D file_dir);
    static string0D convertDigit(int number, int maxNumber);

    static int2D resizeInt2D(int1D vec, int r, int c);
    static long2D resizeLong2D(long1D vec, int r, int c);
    static float2D resizeFloat2D(float1D vec, int r, int c);

    static int1D convertStrInt1D(string0D str, char delimiter = ',');
    static long1D convertStrLong1D(string0D str, char delimiter = ',');
    static float1D convertStrFloat1D(string0D str, char delimiter = ',');

    static int1D convertFloat1DInt(float1D vec);
    static int2D convertFloat2DInt(float2D vec);

};

extern Configuration *CFG;

#endif