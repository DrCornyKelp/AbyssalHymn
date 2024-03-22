#ifndef ENEMY_H
#define ENEMY_H

#include "object2D.h"
#include "projectile.h"

class Player;
class Map;
class Enemy : public Object2D
{
private:
    // Standard stat
    int hp;

    int invincible_time = 0;

    // death come to us all :(
    bool dead = false;
    
    int collide_damage = true;

public:
    Enemy(float X = 0, float Y = 0, int w = 2, int h = 2, int hw = 2, int hh = 2, int sim = 2, int sfm = 20);
    virtual void initEnemy(SDL_Renderer *renderer);

    virtual void draw(SDL_Renderer *renderer, Player *player);

    virtual void enemyAI(Player *player, Map *map);
    virtual void enemyPlayerCollision(Player *player);
    
    void updateEnemy(Player *player, Map *map);

    // Getter
    int getHp();
    bool getDead();
    int getInvinTime();
    int getCollideDamage();

    // Setter
    void setHp(int h);
    void setDead(bool d);
    void setInvinTime(int time);
    int setCollideDamage(int dmg);
};

#endif