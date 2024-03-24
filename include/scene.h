#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <SDL2/SDL.h>

#include "game.h"
#include "sprite.h"
#include "input.h"

class Scene
{
private:
    Sprite *main_menu_bg;
    Sprite *level_select_bg;
public:
    short menu_counter = 0;
    short game_state;   // 0: Main Menu
                        // 1: Level Select
                        // 2: Stage 1 (for testing)
                        // 3: Pause
                        // 4: Quit

    Sprite *getMainMenuBg();
    Sprite *getLevelSelectBg();

    void initMainMenuBg(SDL_Renderer *renderer, const char *path);
    void initLevelSelectBg(SDL_Renderer *renderer, const char *path);
    void mainMenuNavi(Input *Input);
};

#endif