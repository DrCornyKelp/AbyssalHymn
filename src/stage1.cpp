#include "stage1.h"

void Stage1::initBlocks(SDL_Renderer *renderer)
{
    // // Boundary
    // BlockVec.push_back(new Block(-40, 800, 80, 1600));
    // // Gorund
    // BlockVec.push_back(new Block(640, 64, 1280, 128));
    // BlockVec.push_back(new Block(1100, 212, 240, 80));
    // BlockVec.push_back(new Block(1880, 260, 880, 640));
    // // Nridge
    // BlockVec.push_back(new Block(1280, 475, 362, 16));
    
    // Boundary
    // BlockVec.push_back(new Block(-40, 800, 80, 1600));
    // Ground
    // BlockVec.push_back(new Block(500, 100, 1000, 100));
    BlockVec.push_back(new Block("res/Grass.png", 0, 0, 10, 1, 128));
    BlockVec.push_back(new Block("res/Grass.png", 4, 3.5, 10, 1, 128));
    BlockVec.push_back(new Block("res/Grass.png", 4, 1.5, 10, 1, 128));

    // BlockVec.push_back(new Block(1150, 125, 300, 150));
    // BlockVec.push_back(new Block(1450, 200, 300, 100));
    // BlockVec.push_back(new Block(1750, 200, 300, 200));
    // BlockVec.push_back(new Block(2050, 225, 300, 250));

    // BlockVec.push_back(new Block(2500, 350, 100, 50));
    // BlockVec.push_back(new Block(2900, 350, 100, 50));
    // BlockVec.push_back(new Block(3500, 350, 100, 50));

    // BlockVec.push_back(new Block(4000, 275, 200, 300));
    // // BlockVec.push_back(new Block(4200, 525, 200, 100));
    // BlockVec.push_back(new Block(4400, 275, 200, 300));


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
