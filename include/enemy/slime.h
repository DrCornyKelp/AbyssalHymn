#ifndef SLIME_H
#define SLIME_H

#include <cstdlib>
#include <ctime>

#include <enemy.h>
#include <random>

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
    Sprite *moveLeftSprite;
    Sprite *moveRightSprite;
    Sprite *deathSprite;

    Sprite *bulletSprite;

    int time = 0;

public:
    Slime(float X = 0, float Y = 0, float limX1 = 0, float limX2 = 0, short startDir = 1, float scale = 1);
    void initEnemy(SDL_Renderer *renderer) override;

    void enemyAI(Player *player, Map *map) override;
    void enemyPlayerCollision(Player *player) override;
    void draw(SDL_Renderer *renderer, Player* player) override;
};

#endif