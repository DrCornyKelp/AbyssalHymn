#ifndef ENEMY_H
#define ENEMY_H

#include <object2D.h>
#include <projectile.h>

#define Enemy1D std::vector<Enemy*>

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
    
    int collide_damage = 0;

public:
    Enemy(  float X = 0, float Y = 0, int w = 2, int h = 2, int hw = 2, int hh = 2,
            int sw = 0, int sh = 0, int sim = 2, int sfm = 20);
    virtual void initEnemy();

    virtual void draw(Player *player);

    virtual void enemyAI(Map *map);
    virtual void enemyGetHit(int dmg);

    void updateEnemy(Map *map);

    // Getter
    int getHp();
    bool getDead();
    int getInvinTime();
    int getCollideDamage();

    // Setter
    void setHp(int h);
    void setDead(bool d);
    void setInvinTime(int time);
    void setCollideDamage(int dmg);
};

#endif