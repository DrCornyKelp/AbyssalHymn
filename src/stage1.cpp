#include "stage1.h"

void Stage1::initBlocks(SDL_Renderer *renderer)
{
    // Boundary
    BlockVec.push_back(new Block(-40, 800, 80, 1600));
    // Gorund
    BlockVec.push_back(new Block(640, 64, 1280, 128));
    BlockVec.push_back(new Block(1100, 212, 240, 80));
    BlockVec.push_back(new Block(1880, 260, 880, 640));
    // Nridge
    BlockVec.push_back(new Block(1280, 475, 362, 10));

    for (Block *block : BlockVec)
        block->initBlock(renderer, "res/Grass.png");
}

void Stage1::initDecors(SDL_Renderer *renderer)
{

}

void Stage1::initEnemies(SDL_Renderer *renderer)
{
    std::cout << "WIP";
}
