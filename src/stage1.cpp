#include "stage1.h"

void Stage1::initBlocks(SDL_Renderer *renderer)
{
    BlockVec.push_back(new Block(770, 330, 240, 64, false));
    BlockVec.push_back(new Block(755, 480, 210, 64));
    // Boundary
    BlockVec.push_back(new Block(-40, 800, 80, 1600));
    // Gorund
    BlockVec.push_back(new Block(640, 64, 1280, 128));
    // Test Ceiling
    BlockVec.push_back(new Block(640, 240, 128, 128)); 

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
