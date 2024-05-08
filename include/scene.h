#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <SDL2/SDL.h>

#include <configuration.h>
#include <input.h>

class Object2D;
class Scene
{
private:
    SDL_Texture *main_menu_bg;
    SDL_Texture *level_select_bg;
public:
    short menu_counter = 0;
    short game_state;   // 0: Main Menu
                        // 1: Level Select
                        // 2: Stage 1 (for testing)
                        // 3: Pause
                        // 4: Quit

    SDL_Texture *getMainMenuBg();
    SDL_Texture *getLevelSelectBg();

    void initMainMenuBg(const char *path);
    void initLevelSelectBg(const char *path);
    void mainMenuNavi(Input *Input);
};

#endif