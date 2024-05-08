#include <hud.h>

Hud::~Hud()
{
    Object2D::deleteTextures({
        combatReadyTexture, combatDelayTexture, combatChargeTexture,
        jumpTexture, jumpDoubleTexture, jumpSuperTexture,
        invincibleTexture
    });
}
Hud::Hud(Player *p) : player(p)
{
    combatReadyTexture = Object2D::loadTexture("res/HudElement/HeadUp/CombatReady.png");
    combatDelayTexture = Object2D::loadTexture("res/HudElement/HeadUp/CombatDelay.png");
    combatChargeTexture = Object2D::loadTexture("res/HudElement/HeadUp/CombatCharge.png");

    jumpTexture = Object2D::loadTexture("res/HudElement/HeadUp/Jump.png");
    jumpDoubleTexture = Object2D::loadTexture("res/HudElement/HeadUp/JumpDouble.png");
    jumpSuperTexture = Object2D::loadTexture("res/HudElement/HeadUp/JumpSuper.png");

    invincibleTexture = Object2D::loadTexture("res/HudElement/HeadUp/Invincible.png");
}

void Hud::setAlpha(int a)
{ alpha = a; }

void Hud::drawHeadUpStat()
{
    SDL_Rect desRect = {Camera::playerDrawX(player, 128),
                        Camera::playerDrawY(player, 128) -
                        (player->move.crawl ? 0 : 8),
                        128, 128};
    SDL_Rect srcRect = {0, 0, 64, 64};

    // Combat
    if (player->combat.weapon_equip)
    {
        SDL_Texture *combatTexture =
        (player->combat.time || player->combat.delay) ?
            combatDelayTexture : combatReadyTexture;
        combatTexture = player->combat.charge_time > 50 ?
            combatChargeTexture : combatTexture;
        SDL_RenderCopy(CFG->RENDERER, combatTexture, &srcRect, &desRect);
    }

    // Jump 
    if (player->jump.super >= player->jump.super_max)
        SDL_RenderCopy(CFG->RENDERER, jumpSuperTexture, &srcRect, &desRect);
    else if (player->jump.cur == 2)
        SDL_RenderCopy(CFG->RENDERER, jumpTexture, &srcRect, &desRect);
    else if (player->jump.cur == 1)
        SDL_RenderCopy(CFG->RENDERER, jumpDoubleTexture, &srcRect, &desRect);

    // Invincible / Invurnable
    if (player->combat.invincible || player->combat.invulnerable)
        SDL_RenderCopy(CFG->RENDERER, invincibleTexture, &srcRect, &desRect);
}

void Hud::draw()
{
    drawHeadUpStat();
}