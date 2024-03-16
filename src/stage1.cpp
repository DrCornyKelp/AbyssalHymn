#include "stage1.h"

void Stage1::initBlocks(SDL_Renderer *renderer)
{
    // BlockVec.push_back(new Block(770, 330, 240, 64));
    // BlockVec.push_back(new Block(755, 490, 210, 80));
    // Boundary
    BlockVec.push_back(new Block(-40, 800, 80, 1600));
    // // Gorund
    BlockVec.push_back(new Block(640, 64, 1280, 128));
    BlockVec.push_back(new Block(1100, 340, 240, 80));
    BlockVec.push_back(new Block(1880, 260, 880, 640));

    // Gorund
    // BlockVec.push_back(new Block(1280, 64, 2560, 128));

    // BlockVec.push_back(new Block(1500, 240, 100, 64));
    // BlockVec.push_back(new Block(1900, 300, 100, 50));
    // BlockVec.push_back(new Block(2300, 360, 100, 50));

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
