#include <enemy/skeleton.h>
#include <player.h>
#include <map.h>

Skeleton::Skeleton(float X, float Y, float limX1, float limX2) :
    Enemy(X * 64, Y * 64 + 96, 288, 192, 50, 130, 10, 15),
    lim_left(limX1 * 64), lim_right(limX2 * 64)
{}

void Skeleton::initEnemy(SDL_Renderer *renderer)
{
    // Skeleton move
    moveLeftTexture = Sprite::loadTexture(renderer, "res/EnemySheet/Skeleton/MoveLeft.png");
    moveRightTexture = Sprite::loadTexture(renderer, "res/EnemySheet/Skeleton/MoveRight.png");
    
    idleLeftTexture = Sprite::loadTexture(renderer, "res/EnemySheet/Skeleton/IdleLeft.png");
    idleRightTexture = Sprite::loadTexture(renderer, "res/EnemySheet/Skeleton/IdleRight.png");

    attackLeftTexture = Sprite::loadTexture(renderer, "res/EnemySheet/Skeleton/Attack1Left.png");
    attackRightTexture = Sprite::loadTexture(renderer, "res/EnemySheet/Skeleton/Attack1Right.png");

    hurtLeftTexture = Sprite::loadTexture(renderer, "res/EnemySheet/Skeleton/HurtLeft.png");
    hurtRightTexture = Sprite::loadTexture(renderer, "res/EnemySheet/Skeleton/HurtRight.png");

    deathLeftTexture = Sprite::loadTexture(renderer, "res/EnemySheet/Skeleton/DieLeft.png");
    deathRightTexture = Sprite::loadTexture(renderer, "res/EnemySheet/Skeleton/DieRight.png");

    // Skeleton Stat
    setHp(100);
    setCollideDamage(5);
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

void Skeleton::enemyAI(Player *player, Map *map)
{

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

    if (!attack_delay && !attack_state &&
        abs(player->getX() - getX()) < 200 && (
        (direction > 0 && player->getX() > getX()) ||
        (direction < 0 && player->getX() < getX())
    )) {
        setSprIndex(0);
        setSprFrameMax(10);
        attack_state = true;
    }
    if (attack_delay) attack_delay--;

    if (attack_state)
    {
        if (getSprIndex() == getSprIndexMax() - 1 || getInvinTime() > 80)
        {
            setSprIndex(0);
            setSprFrameMax(15);
            attack_delay = 200;
            attack_state = 0;
        }
    }

    if (getInvinTime() < 60 && !idle_time && !attack_state)
        setX(getX() + direction);

    if (getInvinTime())
    {
        setInvinTime(getInvinTime() - 1);
        SDL_SetTextureAlphaMod(skeleTexture, (getInvinTime() % 15 > 0) ? 200 : 160);
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

    skeleTexture = getInvinTime() > 60 ? (
        direction > 0 ? hurtRightTexture : hurtLeftTexture
    ) : skeleTexture;

    skeleTexture = getDead() ? (
        direction > 0 ? deathRightTexture : deathLeftTexture
    ) : skeleTexture;

    setSprIndexMax(idle_time && !attack_state ? 8 : 10);
    if (getInvinTime() && !attack_state)
        setSprIndexMax(5);
    if (getDead())
        setSprIndexMax(10);

    // std::cout << wander_state << " " << wander_time << " " << idle_time << "\n";
}

void Skeleton::enemyPlayerCollision(Player *player)
{

}

void Skeleton::enemyGetHit(int dmg)
{
    if (getInvinTime()) return;

    setSprIndex(0);
    setInvinTime(100);
    setHp(getHp() - dmg);
}

void Skeleton::draw(SDL_Renderer *renderer, Player *player)
{
    // Outside seeable? unrender
    if (Camera::objectOutBound(player, this))
        return;
    // Frame index shitty bang bang stuff handler
    Camera::objectSetSprite(this,
        getInvinTime() > 80 && !attack_state
    );

    // Draw
    double cam_scale = player->getCameraScale();
    SDL_Rect desRect = {Camera::objectDrawX(player, this),
                        Camera::objectDrawY(player, this),
                        int(getWidth() * cam_scale),
                        int(getHeight() * cam_scale)};
    SDL_Rect srcRect = {(direction > 0 ? getSprIndex() : getSprIndexMax() - getSprIndex() - 1) * 96,
                        0, 96, 64};

    if (!getInvinTime()) 
        SDL_SetTextureAlphaMod(skeleTexture, 255);
    SDL_RenderCopy(renderer, skeleTexture, &srcRect, &desRect);
}