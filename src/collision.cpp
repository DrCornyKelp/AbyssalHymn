#include "collision.h"

bool Collision::combatCollision(Object2D *attacker, Object2D *receiver)
{
    int colli_x = abs(attacker->getX() - receiver->getX());
    int colli_y = abs(attacker->getY() - receiver->getY());

    return  (attacker->getX() < receiver->getX() ?
                colli_x < attacker->getCombatHitR() + receiver->getHitWidth() / 2 :
                colli_x < attacker->getCombatHitL() + receiver->getHitWidth() / 2) &&
            (attacker->getY() < receiver->getY() ? 
                colli_y < attacker->getCombatHitU() + receiver->getHitHeight() / 2 :
                colli_y < attacker->getCombatHitD() + receiver->getHitHeight() / 2);
}

bool Collision::playerCombatCollision(Player *player, Object2D *receiver)
{
    int colli_x = abs(player->getHitX() - receiver->getX());
    int colli_y = abs(player->getHitY() - receiver->getY());

    return  (player->getHitX() < receiver->getX() ?
                colli_x < player->getCombatHitR() + receiver->getHitWidth() / 2 :
                colli_x < player->getCombatHitL() + receiver->getHitWidth() / 2) &&
            (player->getY() < receiver->getY() ? 
                colli_y < player->getCombatHitU() + receiver->getHitHeight() / 2 :
                colli_y < player->getCombatHitD() + receiver->getHitHeight() / 2);
}

bool Collision::playerCollision(Player *player, Object2D *obj)
{
    int colli_x = abs(player->getHitX() - obj->getX());
    int colli_y = abs(player->getHitY() - obj->getY());
    int hit_dist_x = (player->getHitWidth() + obj->getHitWidth()) / 2;
    int hit_dist_y = (player->getHitHeight() + obj->getHitHeight()) / 2;

    return colli_x < hit_dist_x && colli_y < hit_dist_y;
};

bool Collision::objectCollision(Object2D *obj1, Object2D *obj2)
{
    int colli_x = abs(obj1->getX() - obj2->getX());
    int colli_y = abs(obj1->getY() - obj2->getY());
    int hit_dist_x = (obj1->getHitWidth() + obj2->getHitWidth()) / 2;
    int hit_dist_y = (obj1->getHitHeight() + obj2->getHitHeight()) / 2;
    
    return colli_x < hit_dist_x && colli_y < hit_dist_y;
}

// Seperate Collision

void Collision::playerBlockCollision(Player *player, std::vector<Block*> BlockVec)
{
    bool on_aleast_ground = false;
    bool hug_aleast_wall = false;
    bool crawl_lock_atleast = false;

    for (Block *block : BlockVec)
    {
        // If block is outside of play/usable view
        // No need to check for SHIT MAN
        block->setOutBound(Camera::objectOutBound(player, block));
        if (block->getOutBound()) continue;

        // Collision Value
        int colli_x = abs(player->getHitX() - block->getX());
        int colli_y = abs(player->getHitY() - block->getY());
        int colli_y_stand = abs(player->getY() - block->getY());

        int hit_dist_x = (player->getHitWidth() + block->getHitWidth()) / 2;
        int hit_dist_y = (player->getHitHeight() + block->getHitHeight()) / 2;
        int hit_dist_y_stand = (80 + block->getHitHeight()) / 2;

        if (block->getSeeThru()) {
            if (colli_x + 10 < hit_dist_x && colli_y + 10 < hit_dist_y)
            {
                if (block->getSeeAlpha() > block->getSeeAlphaMin())
                    block->setSeeAlpha(block->getSeeAlpha() - 5);
            }
            else
            {
                if (block->getSeeAlpha() < 255)
                    block->setSeeAlpha(block->getSeeAlpha() + 5);
            } 
        }

        // If it a go thru block
        // No need hitbox detection
        if (block->getGoThru()) continue;

        block->setHugged(false);
        block->setStepOn(false);
        // Hit Left wall
        if (player->getHitX() < block->getX() && colli_x < hit_dist_x &&
            player->getHitY() < block->getY() + hit_dist_y - 10 &&
            player->getHitY() > block->getY() - hit_dist_y + 10)
        {
            if (player->getCanHugWall() && !player->getOnGround() && !player->getIsADash())
            {
                hug_aleast_wall = true;
                player->setHugWallLeft(true);
                player->setVelX(0);

                player->setX(block->getX() - hit_dist_x + 3);
                block->setHugged(-1);
            }
            else
            {
                player->setX(block->getX() - hit_dist_x);
                if (player->getIsADash() || player->getIsGDash())
                    player->setVelX(-player->getVelX() * .5);
                player->setActRight(true);
            }

            continue;
        }

        // Hit Right wall
        if (player->getHitX() > block->getX() && colli_x < hit_dist_x &&
            player->getHitY() < block->getY() + hit_dist_y - 10 &&
            player->getHitY() > block->getY() - hit_dist_y + 10)
        {
            if (player->getCanHugWall() && !player->getOnGround() && !player->getIsADash())
            {
                hug_aleast_wall = true;
                player->setHugWallRight(true);
                player->setVelX(0);
                
                player->setX(block->getX() + hit_dist_x - 3);
                block->setHugged(1);
            }
            else
            {
                player->setX(block->getX() + hit_dist_x);
                if (player->getIsADash() || player->getIsGDash())
                    player->setVelX(-player->getVelX() * .5);
                player->setActRight(false);
            }

            continue;
        }

        // Ceiling logic
        if ((player->getHitX() < block->getX() + hit_dist_x) &&
            (player->getHitX() > block->getX() - hit_dist_x))
        {
            if (player->getVelY() > 0 && player->getHitY() < block->getY() &&
                colli_y < hit_dist_y - player->getVelY())
            {
                player->setCeilingKnockout(ceiling_knockout_delay);
                player->setY(block->getY() - block->getHeight() / 2 - 40 - player->getVelY());
                player->setVelY(-player->getVelY() * 0.1);
                continue;
            }

            if (player->getOnGround() && player->getY() < block->getY() &&
                colli_y_stand < hit_dist_y_stand)
                crawl_lock_atleast = true;
        }

        // Stand on block
        if (!on_aleast_ground &&
            player->getHitY() > block->getY() &&
            colli_y < hit_dist_y &&
            (player->getHitX() < block->getX() + hit_dist_x) &&
            (player->getHitX() > block->getX() - hit_dist_x))
        {
            if (block->getVelX())
                player->setX(player->getX() + block->getVelX());
            if (block->getVelY())
                player->setY(player->getY() + block->getVelY());
            
            if (!player->getIsCrawl() && !player->getIsGDash())
                player->setY(block->getY() + (block->getHeight() + player->getHitHeight()) / 2 - 1);

            block->setStepOn(true);

            on_aleast_ground = true;
            player->setHugWallLeft(false);
            player->setHugWallRight(false);
            continue;
        }
    }

    player->setOnGround(on_aleast_ground);
    player->setCrawlLock(crawl_lock_atleast);

    if (!hug_aleast_wall)
    {
        player->setHugWallLeft(false);
        player->setHugWallRight(false);
    }
}

void Collision::playerEnemyCollision(Player *player, std::vector<Enemy*> EnemyVec)
{
    for (Enemy *enemy : EnemyVec)
    {
        if (enemy->getDead()) continue;

    // ================== TAKING DAMAGE =======================
        int colli_x = abs(player->getHitX() - enemy->getX());
        int colli_y = abs(player->getHitY() - enemy->getY());

        if (playerCollision(player, enemy))
        {
            if (enemy->getCollideDamage())
                player->playerGetHit(enemy->getCollideDamage());

            // Addition enemy logic
            enemy->enemyPlayerCollision(player);
        }

    // ================== DEALING DAMAGE =======================
        if (player->getWeaponEquip() && !(enemy->getInvinTime()) &&
            (player->getCombatTime() || player->getIsADash() || player->getIsGDash()))
        {
            if (playerCombatCollision(player, enemy))
            {
                enemy->enemyGetHit(player->getCombatDamage());

                // When dash get push back
                if (player->getIsADash() || player->getIsGDash())
                    player->setVelX(-player->getVelX());
            }
        }
    }
}

void Collision::playerItemCollision(Player *player, std::vector<Item*> ItemVec)
{
    for (Item *item : ItemVec)
    {
        if (objectCollision(player, item))
        {
            switch(item->getEffect())
            {
            case 2:
                player->setBuffJumpTime(500);
                break;
            }
        }
    }
}