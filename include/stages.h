#ifndef STAGES_H
#define STAGES_H

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

#include "block.h"
#include "enemies.h"
#include "decoration_dynamic.h"
#include "decoration_static.h"

class Stages
{
private:

public:
    std::vector<Block> BlockVec;
    std::vector<Enemies> EnemyVec;

    virtual void initBlocks(SDL_Renderer *renderer);
    virtual void initDecors(SDL_Renderer *renderer);
    virtual void initEnemies(SDL_Renderer *renderer);

    std::vector<Block>& getBlockVec();
    std::vector<Enemies>& getEnemyVec();
};

#endif