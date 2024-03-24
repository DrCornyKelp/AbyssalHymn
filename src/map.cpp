#include "map.h"

// Player
void Map::initMapPlayer(Player *player)
{
    std::cout << "No player \n";
}

// Npc
void Map::initNpcDialogues(SDL_Renderer *renderer)
{
    std::cout << "No npc \n";
}
void Map::initEnemies(SDL_Renderer *renderer)
{
    std::cout << "No enemy \n";
}

// Block
void Map::initBlocks(SDL_Renderer *renderer)
{
    std::cout << "No block \n";
}

// Cosmetic
void Map::initBackground(SDL_Renderer *renderer)
{
    std::cout << "No background \n";
}
void Map::initBackDecors(SDL_Renderer *renderer)
{
    std::cout << "No decor \n";
}
void Map::initBlocksBack(SDL_Renderer *renderer)
{
    std::cout << "No block \n";
}
void Map::initFrontDecors(SDL_Renderer *renderer)
{
    std::cout << "No decor \n";
}

// Init all
void Map::initAll(SDL_Renderer *renderer, Player *player)
{
    initMapPlayer(player);

    initEnemies(renderer);
    initNpcDialogues(renderer);
    
    initBlocks(renderer);
    
    initBackground(renderer);
    initBackDecors(renderer);
    initBlocksBack(renderer);
    initFrontDecors(renderer);
}

// Exlcusive update
void Map::updateMapExclusive(SDL_Renderer *renderer, Player *player, Input *input)
{
    std::cout << "No exclusive stage logic \n";
}