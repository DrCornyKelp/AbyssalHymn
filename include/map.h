#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <algorithm>

#include "input.h"
#include "player.h"
#include "block.h"
#include "decoration.h"
#include "npc_dialogue.h"
#include "projectile.h"

#include "enemy/slime.h"

#include "block_template.h"
class Map
{
public:
    // =============== ATTRIBUTE =================

    // Npc
    std::vector<Enemy*> EnemyVec;
    std::vector<NpcDialogue*> NpcVec;
    // Block
    std::vector<Block*> BlockVec;
    // Cosmetic
    std::vector<Decoration*> BackgroundVec;
    std::vector<Decoration*> DecorBackVec;
    std::vector<Block*> BlockBackVec;
    std::vector<Decoration*> DecorFrontVec;
    // !!! - No init, only spawn on run time - !!!
    // Projectile
    std::vector<Projectile*> ProjectileVec;
    
    // ================= METHOD ===================
    // Player
    virtual void initMapPlayer(Player *player);
    
    // Npc
    virtual void initEnemies(SDL_Renderer *renderer);
    virtual void initNpcDialogues(SDL_Renderer *renderer);

    // Block
    virtual void initBlocks(SDL_Renderer *renderer);

    // Cosmetic
    virtual void initBackground(SDL_Renderer *renderer);
    virtual void initBackDecors(SDL_Renderer *renderer);
    virtual void initBlocksBack(SDL_Renderer *renderer);
    virtual void initFrontDecors(SDL_Renderer *renderer);

    // Stage stuff idc
    void initAll(SDL_Renderer *renderer, Player *player);
    virtual void updateMapExclusive(SDL_Renderer *renderer, Player *player, Input *input);
};

#endif