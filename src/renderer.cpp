#include "renderer.h"

void Renderer::renderAll(SDL_Renderer *renderer, Player *player, Map *map)
{
    // ============== Performance unintensive (kinda) =================

    for (Decoration *background : map->BackgroundVec)
        background->draw(renderer, player);

    // Back Block
    for (Block *blockBack : map->BlockBackVec)
        blockBack->draw(renderer, player);

    //  Back Decor
    for (Decoration *decorBack : map->DecorBackVec)
        decorBack->draw(renderer, player);

    // Npc Dialouge
    for (NpcDialogue *npc : map->NpcVec)
        npc->draw(renderer, player);

    // Enemies
    for (Enemy *enemy : map->EnemyVec)
        enemy->draw(renderer, player);

    // Draw Player
    player->playerDrawSprite(renderer);

    // Block
    for (Block *block : map->BlockVec)
        block->draw(renderer, player);

    // Projectile
    for (Projectile *projectile : map->ProjectileVec)
        projectile->draw(renderer, player);

    // Front Decor
    for (Decoration *decorFront : map->DecorFrontVec)
        decorFront->draw(renderer, player);

    // UNECESSARY
    player->playerGrid(renderer);
}