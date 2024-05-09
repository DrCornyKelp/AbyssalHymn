#ifndef COLLISION_H
#define COLLISION_H

#include <object2D.h>

class Map;
class Player;
class Collision
{
public:
    static bool combatCollision(Object2D *attacker, Object2D *receiver, int1D offset = {0, 0});
    static bool playerCombatCollision(Player *player, Object2D *receiver, bool isReceiver = 0);
    
    static bool playerCollision(Player *player, Object2D *obj, int1D offset = {0, 0});

    static bool objectCollision(Object2D *obj1, Object2D *obj2, int1D offset = {0, 0});
    static bool hitboxCollision(ObjectHitbox hbox1, ObjectHitbox hbox2, int1D offset = {0, 0});
    static bool boxCollision(ObjectBox box1, ObjectBox box2, int1D offset = {0, 0});

    void playerBlockCollision(Map *map, Player *player);
    void playerEnemyCollision(Map *map, Player *player);
    void playerItemCollision(Map *map, Player *player);
    void playerUpdateCollision(Map *map, Player *player);
};

#endif