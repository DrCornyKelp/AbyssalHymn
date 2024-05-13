#include <renderer.h>

void Renderer::renderGameplay(Map *map)
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
        blockBack->draw(map->MapMulti->MAIN);

    // Back Decor
    for (Decoration *decorBack : map->DecorBackVec)
        decorBack->draw(map->MapMulti->MAIN);

    // Door
    for (Door *door : map->DoorVec)
        door->draw(map->MapMulti->MAIN);

    // Particle Back
    for (ParticleEffect *particle_fx : map->ParticleBackVec)
        particle_fx->draw(map->MapMulti->MAIN);

    // Enemies
    for (Enemy *enemy : map->EnemyVec)
        enemy->draw(map->MapMulti->MAIN);

    // Player
    map->MapMulti->drawPlayers();

    // Projectile
    for (Projectile *projectile : map->ProjectileVec)
        projectile->draw(map->MapMulti->MAIN);

    // Block
    for (Block *block : map->BlockMainVec)
        block->draw(map->MapMulti->MAIN);

    // Hidden Block
    for (Block1D block1d : map->BlockHiddenVec)
    for (Block *block : block1d)
        block->draw(map->MapMulti->MAIN);

    // Bubble Dialouge
    for (Bubble *bubble : map->BubbleVec)
        bubble->draw(map->MapMulti->MAIN);

    // Front Decor
    for (Decoration *decorFront : map->DecorFrontVec)
        decorFront->draw(map->MapMulti->MAIN);

    // Particle Front
    for (ParticleEffect *particle_fx : map->ParticleFrontVec)
        particle_fx->draw(map->MapMulti->MAIN);

    // ==== Developer mode put player above all ====
    if (map->MapMulti->MAIN->getGodmode())
        map->MapMulti->MAIN->draw_prop.draw();

    // Hud
    map->MapMulti->drawHuds();

    // Black Screen
    if (map->MapWorld->map_transition)
        SDL_RenderCopy(CFG->RENDERER, map->MapWorld->BlackScreen, NULL, NULL);
}