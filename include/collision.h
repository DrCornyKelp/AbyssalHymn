#ifndef COLLISION_H
#define COLLISION_H

#include <vector>
#include <object2D.h>

class Map;
class Player;
class Collision
{
private:
    int ceiling_knockout_delay = 50;
public:
    static bool objectCollision(Object2D *obj1, Object2D *obj2);
    static bool combatCollision(Object2D *attacker, Object2D *receiver);
    static bool playerCollision(Player *player, Object2D *obj);
    static bool playerCombatCollision(Player *player, Object2D *receiver);

    void playerBlockCollision(Player *player, Map *map);
    void playerEnemyCollision(Player *player, Map *map);
    void playerItemCollision(Player *player, Map *map);
    void playerUpdateCollision(Player *player, Map *map);
};

#endif