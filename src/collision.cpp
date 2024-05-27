#include <map.h>

// COMBAT COLLIDE
bool Collision::combatCollision(Object2D *attacker, Object2D *receiver, int1D offset)
{
    int colli_x = abs(attacker->hitbox.x - receiver->hitbox.x + offset[0]);
    int colli_y = abs(attacker->hitbox.y - receiver->hitbox.y + offset[1]);

    return  (attacker->hitbox.x < receiver->hitbox.x ?
                colli_x < attacker->combatbox.right + receiver->hitbox.hw / 2 :
                colli_x < attacker->combatbox.left + receiver->hitbox.hw / 2) &&
            (attacker->hitbox.y < receiver->hitbox.y ? 
                colli_y < attacker->combatbox.up + receiver->hitbox.hh / 2 :
                colli_y < attacker->combatbox.down + receiver->hitbox.hh / 2);
}
bool Collision::playerCombatCollision(Player *player, Object2D *receiver, bool isReceiver)
{
    int colli_x = abs(player->move.hitX() - receiver->hitbox.x);
    int colli_y = abs(player->move.hitY() - receiver->hitbox.y);

    return  isReceiver
            ?
            ((player->move.hitX() > receiver->hitbox.x ?
                colli_x < receiver->combatbox.right + player->hitbox.hw / 2 :
                colli_x < receiver->combatbox.left + player->hitbox.hw / 2) &&
            (player->move.hitY() < receiver->hitbox.y ? 
                colli_y < receiver->combatbox.up + player->hitbox.hh / 2 :
                colli_y < receiver->combatbox.down + player->hitbox.hh / 2))
            :
            ((player->move.hitX() < receiver->hitbox.x ?
                colli_x < player->combatbox.right + receiver->hitbox.hw / 2 :
                colli_x < player->combatbox.left + receiver->hitbox.hw / 2) &&
            (player->move.hitY() < receiver->hitbox.y ? 
                colli_y < player->combatbox.up + receiver->hitbox.hh / 2 :
                colli_y < player->combatbox.down + receiver->hitbox.hh / 2));
}

// PLAYER COLLIDE
bool Collision::playerCollision(Player *player, Object2D *obj, int1D offset)
{
    int colli_x = abs(player->move.hitX() - obj->hitbox.x + offset[0]);
    int colli_y = abs(player->move.hitY() - obj->hitbox.y + offset[1]);
    int hit_dist_x = (player->hitbox.hw + obj->hitbox.hw) / 2;
    int hit_dist_y = (player->hitbox.hh + obj->hitbox.hh) / 2;

    return colli_x < hit_dist_x && colli_y < hit_dist_y;
};

// OBJECT COLLIDE
bool Collision::objectCollision(Object2D *obj1, Object2D *obj2, int1D offset)
{
    int colli_x = abs(obj1->hitbox.x - obj2->hitbox.x) + offset[0];
    int colli_y = abs(obj1->hitbox.y - obj2->hitbox.y) + offset[1];
    int hit_dist_x = (obj1->hitbox.hw + obj2->hitbox.hw) / 2;
    int hit_dist_y = (obj1->hitbox.hh + obj2->hitbox.hh) / 2;

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
        int colli_x = abs(player->move.hitX() - enemy->hitbox.x);
        int colli_y = abs(player->move.hitY() - enemy->hitbox.y);

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
                enemy->enemyGetHit(player->combatbox.dmg);

                map->appendParticle(new ParticleEffect(
                    CFG->loadTexture(
                        "assets/ParticleSheet/NakuEffect/Attack.png"),
                    enemy->hitbox.x, enemy->hitbox.y, 100, 100,
                    64, 64, 8, 4, 0
                ));

                // When dash get push back
                if (player->a_dash.frame || player->g_dash.frame)
                    player->vel.x = -player->vel.x;
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
    if (player->dev.godmode) return;

    player->jump.ceiling_min = 20;
    playerBlockCollision(map, player);
    playerEnemyCollision(map, player);
    playerItemCollision(map, player);
}