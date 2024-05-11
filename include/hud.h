#ifndef HUD_H
#define HUD_H

#include <object2D.h>

class Multiplayer;
class Player;
class Hud {
private:
    float alpha = 120; // Opacity

    Player *player;

    int bobbing = 0;
    int bobbing_direction = 1;

    int airbornDisplay = 300;

    // Hud texture
    SDL_Texture *airbornTexture;

    // Head Up texture
    SDL_Texture *combatReadyTexture;
    SDL_Texture *combatDelayTexture;
    SDL_Texture *combatChargeTexture;

    SDL_Texture *jumpTexture;
    SDL_Texture *jumpDoubleTexture;
    SDL_Texture *jumpSuperTexture;

    SDL_Texture *invincibleTexture;
public:
    ~Hud();
    Hud(Player *p);

    // Setter
    void setAlpha(int a);
    // No Getter

    // Alot of drawing
    void drawHeadUpStat();
    void draw();
};

#endif