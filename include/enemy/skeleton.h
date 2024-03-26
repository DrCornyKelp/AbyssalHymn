#ifndef SKELETON_H
#define SKELETON_H

#include <cstdlib>
#include <ctime>

#include <enemy.h>
#include <random>

class Skeleton : public Enemy
{
private:
    int direction = 1;

    SDL_Texture *skeleTexture;

    SDL_Texture *moveLeftTexture;
    SDL_Texture *moveRightTexture;

    SDL_Texture *attackLeftTexture;
    SDL_Texture *attackRightTexture;

    SDL_Texture *hurtLeftTexture;
    SDL_Texture *hurtRightTexture;

    SDL_Texture *deathLeftTexture;
    SDL_Texture *deathRightTexture;
public:
    Skeleton(float X = 0, float Y = 0, float limX1 = 0, float limX2 = 0);
    void initEnemy(SDL_Renderer *renderer) override;

    void enemyAI(Player *player, Map *map) override;
    void enemyPlayerCollision(Player *player) override;
    void enemyGetHit(int dmg) override;
    void draw(SDL_Renderer *renderer, Player* player) override;
};

#endif