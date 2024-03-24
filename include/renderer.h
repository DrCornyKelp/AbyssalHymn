#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

#include "scene.h"
#include "player.h"
#include "block.h"
#include "enemy.h"
#include "map.h"

class Renderer 
{
private:

public:
    void renderGameplay(SDL_Renderer *renderer, Player *player, Map *map);
    void renderMainMenu(SDL_Renderer *renderer, Scene *main_menu);
    void renderLevelSelectMenu(SDL_Renderer *renderer, Scene *main_menu);
};

#endif