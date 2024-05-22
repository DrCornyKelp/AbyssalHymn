#include <map.h>

// COMBAT COLLIDE
bool Collision::combatCollision(Object2D *attacker, Object2D *receiver, int1D offset)
{
    int colli_x = abs(attacker->getX() - receiver->getX() + offset[0]);
    int colli_y = abs(attacker->getY() - receiver->getY() + offset[1]);

    return  (attacker->getX() < receiver->getX() ?
                colli_x < attacker->getCombatHitR() + receiver->getHitWidth() / 2 :
                colli_x < attacker->getCombatHitL() + receiver->getHitWidth() / 2) &&
            (attacker->getY() < receiver->getY() ? 
                colli_y < attacker->getCombatHitU() + receiver->getHitHeight() / 2 :
                colli_y < attacker->getCombatHitD() + receiver->getHitHeight() / 2);
}
bool Collision::playerCombatCollision(Player *player, Object2D *receiver, bool isReceiver)
{
    int colli_x = abs(player->move.hitX() - receiver->getX());
    int colli_y = abs(player->move.hitY() - receiver->getY());

    return  isReceiver
            ?
            ((player->move.hitX() > receiver->getX() ?
                colli_x < receiver->getCombatHitR() + player->getHitWidth() / 2 :
                colli_x < receiver->getCombatHitL() + player->getHitWidth() / 2) &&
            (player->move.hitY() < receiver->getY() ? 
                colli_y < receiver->getCombatHitU() + player->getHitHeight() / 2 :
                colli_y < receiver->getCombatHitD() + player->getHitHeight() / 2))
            :
            ((player->move.hitX() < receiver->getX() ?
                colli_x < player->getCombatHitR() + receiver->getHitWidth() / 2 :
                colli_x < player->getCombatHitL() + receiver->getHitWidth() / 2) &&
            (player->move.hitY() < receiver->getY() ? 
                colli_y < player->getCombatHitU() + receiver->getHitHeight() / 2 :
                colli_y < player->getCombatHitD() + receiver->getHitHeight() / 2));
}

// PLAYER COLLIDE
bool Collision::playerCollision(Player *player, Object2D *obj, int1D offset)
{
    int colli_x = abs(player->move.hitX() - obj->getX() + offset[0]);
    int colli_y = abs(player->move.hitY() - obj->getY() + offset[1]);
    int hit_dist_x = (player->getHitWidth() + obj->getHitWidth()) / 2;
    int hit_dist_y = (player->getHitHeight() + obj->getHitHeight()) / 2;

    return colli_x < hit_dist_x && colli_y < hit_dist_y;
};

// OBJECT COLLIDE
bool Collision::objectCollision(Object2D *obj1, Object2D *obj2, int1D offset)
{
    int colli_x = abs(obj1->getX() - obj2->getX()) + offset[0];
    int colli_y = abs(obj1->getY() - obj2->getY()) + offset[1];
    int hit_dist_x = (obj1->getHitWidth() + obj2->getHitWidth()) / 2;
    int hit_dist_y = (obj1->getHitHeight() + obj2->getHitHeight()) / 2;

    return colli_x <= hit_dist_x && colli_y <= hit_dist_y;
}
bool Collision::hitboxCollision(ObjectHitbox hbox1,
                                ObjectHitbox hbox2,
                                int1D offset)
{
    int colli_x = abs(hbox1.x - hbox2.x) + offset[0];
    int colli_y = abs(hbox1.y - hbox2.y) + offset[1];
    int hit_dist_x = (hbox1.w + hbox2.w) / 2;
    int hit_dist_y = (hbox1.h + hbox2.h) / 2;

    return colli_x <= hit_dist_x && colli_y <= hit_dist_y;
}
bool Collision::boxCollision(ObjectBox box1, ObjectBox box2, int1D offset)
{
    return hitboxCollision(box1.hitbox(), box2.hitbox(), offset);
}

// Seperate Collision

void Collision::playerBlockCollision(Map *map, Player *player)
{
    PlayerState p_state;

    for (Block *block : map->BlockMainVec)
        block->blockCollision(map, player, p_state);
    for (Block *block : map->BlockBackVec)
        block->blockCollision(map, player, p_state);

    player->state = p_state;
}

void Collision::playerEnemyCollision(Map *map, Player *player)
{
    for (Enemy *enemy : map->EnemyVec)
    {
        if (enemy->getDead()) continue;

    // ================== TAKING DAMAGE =======================
        int colli_x = abs(player->move.hitX() - enemy->getX());
        int colli_y = abs(player->move.hitY() - enemy->getY());

        if (playerCollision(player, enemy))
        {
            if (enemy->getCollideDamage())
                player->playerGetHit(map, enemy->getCollideDamage());
        }

    // ================== DEALING DAMAGE =======================
        if (player->combat.weapon_equip &&
            !(enemy->getInvinTime()) &&
            (player->combat.time ||
            player->a_dash.frame ||
            player->g_dash.frame))
        {
            if (playerCombatCollision(player, enemy))
            {
                enemy->enemyGetHit(player->getCombatDamage());

                map->appendParticle(new ParticleEffect(
                    CFG->loadTexture(
                        "assets/ParticleSheet/NakuEffect/Attack.png"),
                    enemy->getX(), enemy->getY(), 100, 100,
                    64, 64, 8, 4, 0
                ));

                // When dash get push back
                if (player->a_dash.frame || player->g_dash.frame)
                    player->setVelX(-player->getVelX());
            }
        }
    }
}

void Collision::playerItemCollision(Map *map, Player *player)
{
    for (Item *item : map->ItemVec)
    {
    }
}

void Collision::playerUpdateCollision(Map *map, Player *player)
{
    if (player->godmode) return;

    player->jump.ceiling_min = 20;
    playerBlockCollision(map, player);
    playerEnemyCollision(map, player);
    playerItemCollision(map, player);
}