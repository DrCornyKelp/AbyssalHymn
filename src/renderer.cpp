#include <renderer.h>

void Renderer::renderGameplay(Map *map, Hud *hud)
{
    // ============== Performance unintensive (kinda) =================

    // Background Color
    SDL_SetRenderDrawColor(CFG->RENDERER,
        map->MapColor.R, map->MapColor.G, map->MapColor.B,
    255);
    SDL_RenderClear(CFG->RENDERER);

    // Background
    for (Decoration *background : map->BackgroundVec)
        background->drawBackground();

    // Back Block
    for (Block *blockBack : map->BlockBackVec)
        blockBack->draw(map->MapPlayers->MAIN);

    // Back Decor
    for (Decoration *decorBack : map->DecorBackVec)
        decorBack->drawDecoration(map->MapPlayers->MAIN);

    // Door
    for (Door *door : map->DoorVec)
        door->draw(map->MapPlayers->MAIN);

    // Particle Back
    for (ParticleEffect *particle_fx : map->ParticleBackVec)
        particle_fx->draw(map->MapPlayers->MAIN);

    // Enemies
    for (Enemy *enemy : map->EnemyVec)
        enemy->draw(map->MapPlayers->MAIN);

    // Player
    map->MapPlayers->draw();

    // Projectile
    for (Projectile *projectile : map->ProjectileVec)
        projectile->draw(map->MapPlayers->MAIN);

    // Block
    for (Block *block : map->BlockMainVec)
        block->draw(map->MapPlayers->MAIN);

    // Hidden Block
    for (Block1D block1d : map->BlockHiddenVec)
    for (Block *block : block1d)
        block->draw(map->MapPlayers->MAIN);

    // Bubble Dialouge
    for (Bubble *bubble : map->BubbleVec)
        bubble->draw(map->MapPlayers->MAIN);

    // Front Decor
    for (Decoration *decorFront : map->DecorFrontVec)
        decorFront->drawDecoration(map->MapPlayers->MAIN);

    // Particle Front
    for (ParticleEffect *particle_fx : map->ParticleFrontVec)
        particle_fx->draw(map->MapPlayers->MAIN);

    // ==== Developer mode put player above all ====
    if (map->MapPlayers->MAIN->getGodmode())
        map->MapPlayers->MAIN->draw_prop.playerDrawSprite();

    // ==== However, developer mode eat shit when it come to hud lmao ====
    // Player Hud
    hud->draw();

    // Black Screen
    if (map->MapWorld->map_transition)
        SDL_RenderCopy(CFG->RENDERER, map->MapWorld->BlackScreen, NULL, NULL);
}

void Renderer::renderMainMenu(Scene *scene)
{
    SDL_RenderCopy(CFG->RENDERER, scene->getMainMenuBg(), NULL, NULL);

    SDL_SetRenderDrawColor(CFG->RENDERER, 255, 0, 0, 100);
    SDL_Rect box = {480, 300 + scene->menu_counter*100, 160, 100};
    SDL_RenderFillRect(CFG->RENDERER, &box);
}

void Renderer::renderLevelSelectMenu(Scene *scene)
{
    SDL_RenderCopy(CFG->RENDERER, scene->getLevelSelectBg(), NULL, NULL);
    // SDL_SetRenderDrawColor(255, 0, 0, 200);
    // SDL_Rect box = {480, 300 + scene->menu_counter*100, 160, 100};
    // SDL_RenderFillRect(&box);
}