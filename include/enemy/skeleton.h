#ifndef SKELETON_H
#define SKELETON_H

#include <cstdlib>
#include <ctime>

#include <enemy.h>

class Skeleton : public Enemy
{
private:
    int direction = 1;
    int lim_left = 0;
    int lim_right = 0;

    bool wander_state = true;
    int wander_time = 100;
    int idle_time = 0;

    int stunt_resistance = 0;
    bool attack_state = false;
    int attack_delay = 0;

    SDL_Texture *skeleTexture;

    SDL_Texture *moveLeftTexture;
    SDL_Texture *moveRightTexture;

    SDL_Texture *idleLeftTexture;
    SDL_Texture *idleRightTexture;

    SDL_Texture *attackLeftTexture;
    SDL_Texture *attackRightTexture;

    SDL_Texture *hurtLeftTexture;
    SDL_Texture *hurtRightTexture;

    SDL_Texture *deathLeftTexture;
    SDL_Texture *deathRightTexture;
public:
    Skeleton(float X = 0, float Y = 0, float limX1 = 0, float limX2 = 0);
    void initEnemy() override;

    int generateRandomDistance();

    void enemyAI(Map *map) override;
    void enemyGetHit(int dmg) override;
    void draw(Player* player) override;
};

#endif