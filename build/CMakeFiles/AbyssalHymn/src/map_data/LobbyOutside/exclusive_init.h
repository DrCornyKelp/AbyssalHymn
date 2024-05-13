#include <map.h>

void LobbyOutsideInit(Map *map)
{
    Slime *slime = new Slime(30, 5, 27, 33);
    slime->initEnemy();

    Skeleton *skeleton = new Skeleton(55, 5, 49, 60);
    skeleton->initEnemy();

    map->EnemyVec.push_back(slime);
    map->EnemyVec.push_back(skeleton);
}