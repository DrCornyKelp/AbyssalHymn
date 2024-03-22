#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

#include "player.h"
#include "block.h"
#include "enemy.h"
#include "map.h"

class Renderer 
{
private:

public:
    void renderAll(SDL_Renderer *renderer, Player *player, Map *map);
};

#endif