#include "renderer.h"

void Renderer::renderGameplay(SDL_Renderer *renderer, Player *player, Hud *hud, Map *map)
{
    // ============== Performance unintensive (kinda) =================

    // Background
    for (Decoration *background : map->BackgroundVec)
        background->draw(renderer, player);

    // Back Block
    for (Block *blockBack : map->BlockBackVec)
        blockBack->draw(renderer, player);

    // Back Decor
    for (Decoration *decorBack : map->DecorBackVec)
        decorBack->draw(renderer, player);

    // Particle Back
    for (ParticleEffect *particle_fx : map->ParticleBackVec)
        particle_fx->draw(renderer, player);

    // Npc Dialouge
    for (NpcDialogue *npc : map->NpcVec)
        npc->draw(renderer, player);

    // Enemies
    for (Enemy *enemy : map->EnemyVec)
        enemy->draw(renderer, player);

    // Player
    player->playerDrawSprite(renderer);

    // Projectile
    for (Projectile *projectile : map->ProjectileVec)
        projectile->draw(renderer, player);

    // Block
    for (Block *block : map->BlockVec)
        block->draw(renderer, player);

    // Front Decor
    for (Decoration *decorFront : map->DecorFrontVec)
        decorFront->draw(renderer, player);

    // Particle Front
    for (ParticleEffect *particle_fx : map->ParticleFrontVec)
        particle_fx->draw(renderer, player);

    // Player Hud
    hud->draw(renderer);

    // UNECESSARY
    player->playerGrid(renderer);
}

void Renderer::renderMainMenu(SDL_Renderer *renderer, Scene *scene)
{
    SDL_Rect menu_bg = {0, 0, Game::WIDTH, Game::HEIGHT};
    SDL_RenderCopy(renderer, scene->getMainMenuBg()->getTexture(), NULL, &menu_bg);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
    SDL_Rect box = {480, 300 + scene->menu_counter*100, 160, 100};
    SDL_RenderFillRect(renderer, &box);
}

void Renderer::renderLevelSelectMenu(SDL_Renderer *renderer, Scene *scene)
{
    SDL_Rect menu_bg = {0, 0, Game::WIDTH, Game::HEIGHT};
    SDL_RenderCopy(renderer, scene->getLevelSelectBg()->getTexture(), NULL, &menu_bg);
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);
    // SDL_Rect box = {480, 300 + scene->menu_counter*100, 160, 100};
    // SDL_RenderFillRect(renderer, &box);
}