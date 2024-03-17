#include "stage1.h"

void Stage1::initBlocks(SDL_Renderer *renderer)
{
    // Ground
    BlockVec.push_back(new Block("res/Grass.png", 0, 0, 10, 1, 128));
    // BlockVec.push_back(new Block("res/Grass.png", 4, 3.5, 10, 1, 128));
    // BlockVec.push_back(new Block("res/Grass.png", 4, 1.5, 10, 1, 128));



    for (Block *block : BlockVec)
        block->initBlock(renderer);
}

void Stage1::initDecors(SDL_Renderer *renderer)
{

}

void Stage1::initEnemies(SDL_Renderer *renderer)
{
    std::cout << "WIP";
}
