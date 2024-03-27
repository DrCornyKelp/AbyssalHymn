#ifndef COLLISION_H
#define COLLISION_H

#include <vector>

#include "player.h"
#include "block.h"
#include "enemy.h"
#include "item.h"

class Collision
{
private:
    int ceiling_knockout_delay = 50;
public:
    static bool playerCollision(Player *player, Object2D *obj);
    static bool combatCollision(Player *player, Object2D *obj);
    static bool objectCollision(Object2D *obj1, Object2D *obj2);

    void playerBlockCollision(Player *player, std::vector<Block*> Blockvec);
    void playerEnemyCollision(Player *player, std::vector<Enemy*> EnemyVec);
    void playerItemCollision(Player *player, std::vector<Item*> ItemVec);
};

#endif