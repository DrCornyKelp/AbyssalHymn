#ifndef SLIME_H
#define SLIME_H

#include <cstdlib>
#include <ctime>

#include <enemy.h>

class Player;
class Map;
class Slime : public Enemy
{
private:
    int color = 0;
    short direction = 1;

    float vel_x = 0;
    float vel_y = 0;

    float limLeft;
    float limRight;

    SDL_Texture *slimeTexture;
    SDL_Texture *moveLeftTexture;
    SDL_Texture *moveRightTexture;
    SDL_Texture *deathTexture;

    SDL_Texture *bulletTexture;

    int time = 0;

public:
    Slime(float X = 0, float Y = 0, float limX1 = 0, float limX2 = 0, short startDir = 1, float scale = 1);
    void initEnemy() override;

    void enemyAI(Map *map) override;
    void enemyGetHit(int dmg) override;
    void draw(Player* player) override;
};

#endif