#include <hud.h>

Hud::Hud(SDL_Renderer *renderer, Player *p) : player(p)
{
    airbornTexture = Sprite::loadTexture(renderer, "res/HudElement/AirBorne.png");
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

    if (airbornDisplay > airReal) {
        airbornDisplay -= 20 / airMax;
    } 
    if (airbornDisplay < airReal)
    {
        airbornDisplay += 20;
    }

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

void Hud::draw(SDL_Renderer *renderer)
{   
    drawAirborne(renderer);
}