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
    moveLeftTexture = loadTexture("res/EnemySheet/Skeleton/MoveLeft.png");
    moveRightTexture = loadTexture("res/EnemySheet/Skeleton/MoveRight.png");
    
    idleLeftTexture = loadTexture("res/EnemySheet/Skeleton/IdleLeft.png");
    idleRightTexture = loadTexture("res/EnemySheet/Skeleton/IdleRight.png");

    attackLeftTexture = loadTexture("res/EnemySheet/Skeleton/Attack1Left.png");
    attackRightTexture = loadTexture("res/EnemySheet/Skeleton/Attack1Right.png");

    hurtLeftTexture = loadTexture("res/EnemySheet/Skeleton/HurtLeft.png");
    hurtRightTexture = loadTexture("res/EnemySheet/Skeleton/HurtRight.png");

    deathLeftTexture = loadTexture("res/EnemySheet/Skeleton/DieLeft.png");
    deathRightTexture = loadTexture("res/EnemySheet/Skeleton/DieRight.png");

    // Skeleton Stat
    setHp(100);
    setCollideDamage(5);
}

void Skeleton::draw(Player *player)
{
    // Outside seeable? unrender
    if (Camera::objectIgnore(player, this))
        return;
    // Frame index shitty bang bang stuff handler
    objectSetSprite( getInvinTime() > 80 && !attack_state );

    // Draw
    SDL_Rect desRect = {Camera::objectDrawX(player, this),
                        Camera::objectDrawY(player, this),
                        getWidth(), getHeight()};
    SDL_Rect srcRect = {(direction > 0 ? getSprIndex() : getSprIndexMax() - getSprIndex() - 1) * 96,
                        0, 96, 64};

    if (!getInvinTime()) 
        SDL_SetTextureAlphaMod(skeleTexture, 255);
    SDL_RenderCopy(CFG->RENDERER, skeleTexture, &srcRect, &desRect);
}

int Skeleton::generateRandomDistance() {
    srand((unsigned) time(NULL));

    int dist = direction > 0 ?  lim_right - getX():
                                getX() - lim_left;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::mt19937::result_type> dis(0, dist);

    return dis(gen);
}

void Skeleton::enemyAI(Map *map)
{
    if (getDead())
    {
        if (getSprIndex() == getSprIndexMax() - 1)
            map->ParticleBackVec.push_back(new ParticleEffect(
                loadTexture(
                    "res/ParticleSheet/Explode.png"),
                getX(), getY(), 120, 120,
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

        if (getX() < lim_left || getX() > lim_right)
        {
            wander_time = 0;
            idle_time = 100;
            wander_state = 0;
        };
    }

    for (Player *player : map->MapPlayers->Players)
    {
        if (!attack_delay && !attack_state &&
            abs(player->getX() - getX()) < 150 && (
            (direction > 0 && player->getX() > getX()) ||
            (direction < 0 && player->getX() < getX())
        )) {
            setSprIndex(0);
            setSprFrameMax(10);
            attack_state = true;
        }

        if (Collision::playerCombatCollision(player, this, true))
        {
            if (!player->combat.invulnerable)
            {
                map->ParticleBackVec.push_back(new ParticleEffect(
                    loadTexture(
                        "res/ParticleSheet/NakuEffect/Attack.png"),
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
        if ((getSprIndex() == getSprIndexMax() - 1) ||
            (getInvinTime() > 60 && !stunt_resistance))
        {
            setSprIndex(0);
            setSprFrameMax(15);
            attack_delay = 200;
            attack_state = 0;
        }
    }

    if (attack_state && getSprIndex() == 4)
    {
        setCombatHitU(40);
        setCombatHitD(40);
        setCombatHitL(direction > 0 ? 0 : 120);
        setCombatHitR(direction > 0 ? 120 : 0);
    }
    else
    {
        setCombatHitU(0);
        setCombatHitD(0);
        setCombatHitL(0);
        setCombatHitR(0);
    }

    if ((getInvinTime() < 60 || stunt_resistance) && !idle_time && !attack_state)
        setX(getX() + direction);

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
        setSprIndex(0);
        setSprFrameMax(20);
        setSprFrameMax(5);
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

    setSprIndexMax(idle_time && !attack_state ? 8 : 10);
    if (getInvinTime() > 60 && !stunt_resistance)
        setSprIndexMax(5);
    if (getDead())
        setSprIndexMax(10);

    // std::cout << wander_state << " " << wander_time << " " << idle_time << "\n";
    // std::cout << attack_state << " " << stunt_resistance << "\n";
}

void Skeleton::enemyGetHit(int dmg)
{
    if (getInvinTime()) return;

    if (!stunt_resistance)
        setSprIndex(0);

    setInvinTime(100);
    setHp(getHp() - dmg);
}