#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <algorithm>

#include "input.h"
#include "block_template.h"
#include "collision.h"

#include "item.h"
#include "block.h"
#include "player.h"
#include "decoration.h"
#include "projectile.h"
#include "npc_dialogue.h"
#include "particle_effect.h"

#include "enemy/all_enemies.h"

class Map
{
public:
    // =============== ATTRIBUTE =================
    SDL_Renderer *Renderer;

    // Npc
    std::vector<Enemy*> EnemyVec;
    std::vector<NpcDialogue*> NpcVec;
    // Particle_Effect
    std::vector<ParticleEffect*> ParticleBackVec;
    std::vector<ParticleEffect*> ParticleFrontVec;
    // Block
    std::vector<Block*> BlockVec;
    // Item
    std::vector<Item*> ItemVec;
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

    // Paricle Effect
    virtual void initParticleBack(SDL_Renderer *renderer);
    virtual void initParticleFront(SDL_Renderer *renderer);

    // Block
    virtual void initBlocks(SDL_Renderer *renderer);

    // Items
    virtual void initItems(SDL_Renderer *renderer);

    // Cosmetic
    virtual void initBackground(SDL_Renderer *renderer);
    virtual void initBackDecors(SDL_Renderer *renderer);
    virtual void initBlocksBack(SDL_Renderer *renderer);
    virtual void initFrontDecors(SDL_Renderer *renderer);

    // Stage stuff idc
    void initAll(SDL_Renderer *renderer, Player *player);
    virtual void updateMapExclusive(SDL_Renderer *renderer, Player *player, Input *input, Collision *collision);
};

#endif