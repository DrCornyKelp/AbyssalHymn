#include "enemy.h"
#include "player.h"
#include "map.h"

Enemy::Enemy(float X, float Y, int w, int h, int hw, int hh, int sim, int sfm) :
    Object2D(X, Y, w, h, hw, hh,
            sim, sfm, 0, 0)
{}

void Enemy::initEnemy(SDL_Renderer *renderer)
{
    std::cout << "no enemy \n";
}

void Enemy::draw(SDL_Renderer *renderer, Player *player)
{
    std::cout << "no enemy sprite \n";
}

void Enemy::enemyAI(Player *player, Map *map)
{
    std::cout << "no enemy AI \n";
}

void Enemy::enemyPlayerCollision(Player *player)
{
    std::cout << "enemy friendly af \n";
}

void Enemy::updateEnemy(Player *player, Map *map)
{
    if (!dead)
    {
        enemyAI(player, map);
        enemyPlayerCollision(player);
    }
}

// Getter
int Enemy::getHp()
{
    return hp;
};
bool Enemy::getDead()
{
    return dead;
};
int Enemy::getInvinTime()
{
    return invincible_time;
};

// Setter
void Enemy::setHp(int h)
{
    hp = h;
};
void Enemy::setDead(bool d)
{
    dead = d;
};
void Enemy::setInvinTime(int time)
{
    invincible_time = time;
};