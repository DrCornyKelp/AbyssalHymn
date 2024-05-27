#include <enemy/skeleton.h>
#include <player.h>
#include <map.h>

Skeleton::Skeleton(float X, float Y, float limX1, float limX2) :
    Enemy(X * 64, Y * 64 + 96, 288, 192, 45, 120,
        96, 64, 10, 15),
    lim_left(limX1 * 64), lim_right(limX2 * 64)
{}

void Skeleton::initEnemy()
{
    // Skeleton move
    moveLeftTexture = CFG->loadTexture("assets/EnemySheet/Skeleton/MoveLeft.png");
    moveRightTexture = CFG->loadTexture("assets/EnemySheet/Skeleton/MoveRight.png");
    
    idleLeftTexture = CFG->loadTexture("assets/EnemySheet/Skeleton/IdleLeft.png");
    idleRightTexture = CFG->loadTexture("assets/EnemySheet/Skeleton/IdleRight.png");

    attackLeftTexture = CFG->loadTexture("assets/EnemySheet/Skeleton/Attack1Left.png");
    attackRightTexture = CFG->loadTexture("assets/EnemySheet/Skeleton/Attack1Right.png");

    hurtLeftTexture = CFG->loadTexture("assets/EnemySheet/Skeleton/HurtLeft.png");
    hurtRightTexture = CFG->loadTexture("assets/EnemySheet/Skeleton/HurtRight.png");

    deathLeftTexture = CFG->loadTexture("assets/EnemySheet/Skeleton/DieLeft.png");
    deathRightTexture = CFG->loadTexture("assets/EnemySheet/Skeleton/DieRight.png");

    // Skeleton Stat
    setHp(100);
    setCollideDamage(5);
}

void Skeleton::draw(Player *player)
{
    // Frame index shitty bang bang stuff handler
    setSprite( getInvinTime() > 80 && !attack_state );

    // Draw
    SDL_Rect desRect = {Camera::objectDrawX(player, this),
                        Camera::objectDrawY(player, this),
                        int(hitbox.w), int(hitbox.h)};
    SDL_Rect srcRect = {(direction > 0 ? sprite.si : sprite.sim - sprite.si - 1) * 96,
                        0, 96, 64};

    if (!getInvinTime()) 
        SDL_SetTextureAlphaMod(skeleTexture, 255);
    SDL_RenderCopy(CFG->RENDERER, skeleTexture, &srcRect, &desRect);
}

int Skeleton::generateRandomDistance() {
    srand((unsigned) time(NULL));

    int dist = direction > 0 ?  lim_right - hitbox.x:
                                hitbox.x - lim_left;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::mt19937::result_type> dis(0, dist);

    return dis(gen);
}

void Skeleton::enemyAI(Map *map)
{
    if (getDead())
    {
        if (sprite.si == sprite.sim - 1)
            map->appendParticle(new ParticleEffect(
                CFG->loadTexture(
                    "assets/ParticleSheet/Explode.png"),
                hitbox.x, hitbox.y, 120, 120,
                100, 100, 10, 7, 3, 0
            ));

        return;
    }

    if (!attack_state)
    {
        if (wander_time && wander_state)
        {
            wander_time--;
            if (!wander_time)
            {
                wander_state = 0;
                idle_time = 200;
            }
        }

        if (idle_time && !wander_state)
        {
            idle_time--;
            if (!idle_time)
            {
                wander_state = true;
                direction = -direction;
                wander_time = generateRandomDistance();
            }
        }

        if (hitbox.x < lim_left || hitbox.x > lim_right)
        {
            wander_time = 0;
            idle_time = 100;
            wander_state = 0;
        };
    }

    for (Player *player : map->MapMulti->Players)
    {
        if (!attack_delay && !attack_state &&
            abs(player->hitbox.x - hitbox.x) < 150 && (
            (direction > 0 && player->hitbox.x > hitbox.x) ||
            (direction < 0 && player->hitbox.x < hitbox.x)
        )) {
            sprite.si = 0;
            sprite.sfm = 10;
            attack_state = true;
        }

        if (Collision::playerCombatCollision(player, this, true))
        {
            if (!player->combat.invulnerable)
            {
                map->appendParticle(new ParticleEffect(
                    CFG->loadTexture(
                        "assets/ParticleSheet/NakuEffect/Attack.png"),
                    player->move.hitX(), player->move.hitY(), 100, 100,
                    64, 64, 8, 4, 0
                ));
            }
            player->playerGetHit(map, 20);
        }
    }

    if (attack_delay) attack_delay--;
    if (stunt_resistance) stunt_resistance--;

    if (attack_state)
    {
        if ((sprite.si == sprite.sim - 1) ||
            (getInvinTime() > 60 && !stunt_resistance))
        {
            sprite.si = 0;
            sprite.sfm = 15;
            attack_delay = 200;
            attack_state = 0;
        }
    }

    if (attack_state && sprite.si == 4)
    {
        combatbox = {
            40, 40, direction > 0 ? 0 : 120, direction > 0 ? 120 : 0
        };
    }
    else
        combatbox = {};

    if ((getInvinTime() < 60 || stunt_resistance) && !idle_time && !attack_state)
        hitbox.x += direction;

    if (getInvinTime())
    {
        setInvinTime(getInvinTime() - 1);
        SDL_SetTextureAlphaMod(skeleTexture, (getInvinTime() % 15 > 0) ? 200 : 160);

        if (!getInvinTime() && !stunt_resistance)
            stunt_resistance = 300;
    }

    if (getHp() <= 0)
    {
        setDead(true);
        sprite.si = 0;
        sprite.sfm = 20;
        sprite.sim = 5;
    };

    skeleTexture = direction > 0 ? moveRightTexture : moveLeftTexture;
    skeleTexture = !idle_time ? skeleTexture : (
        direction > 0 ? idleRightTexture : idleLeftTexture
    );

    skeleTexture = !attack_state ? skeleTexture : (
        direction > 0 ? attackRightTexture : attackLeftTexture
    );

    skeleTexture = (getInvinTime() > 60 && !stunt_resistance) ? (
        direction > 0 ? hurtRightTexture : hurtLeftTexture
    ) : skeleTexture;

    skeleTexture = getDead() ? (
        direction > 0 ? deathRightTexture : deathLeftTexture
    ) : skeleTexture;

    sprite.sim = idle_time && !attack_state ? 8 : 10;
    if (getInvinTime() > 60 && !stunt_resistance)
        sprite.sim = 5;
    if (getDead())
        sprite.sim = 10;

    // std::cout << wander_state << " " << wander_time << " " << idle_time << "\n";
    // std::cout << attack_state << " " << stunt_resistance << "\n";
}

void Skeleton::enemyGetHit(int dmg)
{
    if (getInvinTime()) return;

    if (!stunt_resistance)
        sprite.si = 0;

    setInvinTime(100);
    setHp(getHp() - dmg);
}