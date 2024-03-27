#include <hud.h>

Hud::Hud(SDL_Renderer *renderer, Player *p) : player(p)
{
    airbornTexture = Sprite::loadTexture(renderer, "res/HudElement/AirBorne.png");

    combatReadyTexture = Sprite::loadTexture(renderer, "res/HudElement/HeadUp/CombatReady.png");
    combatDelayTexture = Sprite::loadTexture(renderer, "res/HudElement/HeadUp/CombatDelay.png");
    combatChargeTexture = Sprite::loadTexture(renderer, "res/HudElement/HeadUp/CombatCharge.png");
    
    superJumpReadyTexture = Sprite::loadTexture(renderer, "res/HudElement/HeadUp/SuperJumpReady.png");
    invincibleTexture = Sprite::loadTexture(renderer, "res/HudElement/HeadUp/Invincible.png");
}
void Hud::setAlpha(int a)
{
    alpha = a;
}

void Hud::drawHealth(SDL_Renderer *renderer)
{
    float hpCur = player->getHpCur();
    float hpMax = player->getHpMax();
}
void Hud::drawAirborne(SDL_Renderer *renderer)
{
    float airCur = player->getAirCur();
    float airMax = player->getAirMax();

    float airRatio = airCur / airMax;
    int barLength = 360 / airMax;
    int airReal = barLength * airCur;

    if (airbornDisplay > airReal) 
        airbornDisplay -= 20 / airMax;

    if (airbornDisplay < airReal)
        airbornDisplay += 20;

    int bar_h = 40;
    int bar_off = 10;

    int bar_down = 0;

    SDL_Rect iconRect = {0, bar_down, bar_h, bar_h};
    SDL_RenderCopy(renderer, airbornTexture, NULL, &iconRect);
    
    int green = 200 * (airRatio);
    int red = 200 * (1 - (airCur - 1) / airMax);
    SDL_SetRenderDrawColor(renderer, red, green, 50, 255);
    SDL_Rect inRect = {bar_h, bar_off + bar_down, airbornDisplay, bar_h - bar_off * 2};
    SDL_RenderFillRect(renderer, &inRect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < airMax; i++) {
        SDL_Rect rect = {bar_h + i * barLength, bar_off + bar_down, barLength, bar_h - bar_off * 2};
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void Hud::drawHeadUpStat(SDL_Renderer *renderer)
{
    double cam_scale = player->getCameraScale();
    int drawX = Game::WIDTH / 2 + (player->getOffsetMidX() - 64) * cam_scale;
    int drawY = Game::HEIGHT / 2 - (player->getOffsetMidY() + 64 - (player->getIsCrawl() ? 10 : 0)) * cam_scale;

    SDL_Rect desRect = {drawX + Camera::playerShiftX(player),
                        drawY + Camera::playerShiftY(player) - 5,
                        int(128 * cam_scale),
                        int(128 * cam_scale)};
    SDL_Rect srcRect = {0, 0, 64, 64};

    if (player->getWeaponEquip())
    {
        SDL_Texture *combatTexture =
        (player->getCombatTime() || player->getCombatDelay()) ?
            combatDelayTexture : combatReadyTexture;
        combatTexture = player->getCombatCharge() > 50 ? combatChargeTexture : combatTexture;
        SDL_RenderCopy(renderer, combatTexture, &srcRect, &desRect);
    }
    
    if (player->getSuperJump())
        SDL_RenderCopy(renderer, superJumpReadyTexture, &srcRect, &desRect);
    
    if (player->getInvincibleTime() || player->getInvulnerableTime())
        SDL_RenderCopy(renderer, invincibleTexture, &srcRect, &desRect);
}

void Hud::draw(SDL_Renderer *renderer)
{
    drawHeadUpStat(renderer);
    drawAirborne(renderer);
}