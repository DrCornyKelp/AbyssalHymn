#include <renderer.h>

void Renderer::renderGameplay(Map *map)
{
    // Background Color / Clear Render for next drawing iteration
    SDL_SetRenderDrawColor(CFG->RENDERER,
        map->MapColor.R, map->MapColor.G, map->MapColor.B,
    255);
    SDL_RenderClear(CFG->RENDERER);

    // Background
    for (Decoration *background : map->BackgroundVec)
        background->drawBackground();

    // Back Block
    for (Block *blockBack : map->BlockBackVec)
        blockBack->draw(map->MULTI->MAIN);

    // Back Decor
    for (Decoration *decorBack : map->DecorBackVec)
        decorBack->draw(map->MULTI->MAIN);

    // Door
    for (Door *door : map->DoorVec)
        door->draw(map->MULTI->MAIN);

    // Particle Back
    for (ParticleEffect *particle_fx : map->ParticleBackVec)
        particle_fx->draw(map->MULTI->MAIN);

    // Enemies
    for (Enemy *enemy : map->EnemyVec)
        enemy->draw(map->MULTI->MAIN);

    // Player
    map->MULTI->drawPlayers();

    // Projectile
    for (Projectile *projectile : map->ProjectileVec)
        projectile->draw(map->MULTI->MAIN);

    // Block
    for (Block *block : map->BlockMainVec)
        block->draw(map->MULTI->MAIN);

    // Hidden Block
    for (Block1D block1d : map->BlockHiddenVec)
    for (Block *block : block1d)
        block->draw(map->MULTI->MAIN);

    // Bubble Dialouge
    for (Bubble *bubble : map->BubbleVec)
        bubble->draw(map->MULTI);

    // Front Decor
    for (Decoration *decorFront : map->DecorFrontVec)
        decorFront->draw(map->MULTI->MAIN);

    // Particle Front
    for (ParticleEffect *particle_fx : map->ParticleFrontVec)
        particle_fx->draw(map->MULTI->MAIN);

    // ==== Developer mode put player above all ====
    if (map->MULTI->MAIN->dev.godmode)
        map->MULTI->MAIN->psprite.draw();

    // Hud
    map->MULTI->drawHuds();
}