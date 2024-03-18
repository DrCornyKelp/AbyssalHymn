#include "stages.h"

void Stages::initBlocks(SDL_Renderer *renderer)
{
    std::cout << "No block" << "\n";
}

void Stages::initDecors(SDL_Renderer *renderer)
{
    std::cout << "No decor" << "\n";
}

void Stages::initEnemies(SDL_Renderer *renderer)
{
    std::cout << "No enemy" << "\n";
}

std::vector<Block*> Stages::getBlockVec()
{
    return BlockVec;
}

// std::vector<Enemies*>& Stages::getEnemyVec()
// {
//     return EnemyVec;
// }