#include <enemy/skeleton.h>
#include <player.h>
#include <map.h>

Skeleton::Skeleton(float X, float Y, float limX1, float limX2) :
    Enemy(X * 64, Y * 64 + 96, 288, 192, 35, 64, 10, 15)
{}

void Skeleton::initEnemy(SDL_Renderer *renderer)
{
    // Skeleton move
    moveLeftTexture = Sprite::loadTexture(renderer, "res/EnemySheet/Skeleton/MoveLeft.png");
    moveRightTexture = Sprite::loadTexture(renderer, "res/EnemySheet/Skeleton/MoveRight.png");
    
    deathLeftTexture = Sprite::loadTexture(renderer, "res/EnemySheet/Skeleton/DieLeft.png");
    deathRightTexture = Sprite::loadTexture(renderer, "res/EnemySheet/Skeleton/DieRight.png");
    
    hurtLeftTexture = Sprite::loadTexture(renderer, "res/EnemySheet/Skeleton/HurtLeft.png");
    hurtRightTexture = Sprite::loadTexture(renderer, "res/EnemySheet/Skeleton/HurtRight.png");

    // Skeleton Stat
    setHp(100);
    setCollideDamage(5);
}

void Skeleton::enemyAI(Player *player, Map *map)
{
    if (getX() > 17 * 64) direction = -1;
    if (getX() < 1 * 64) direction = 1;
    if (getInvinTime() < 60)
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

    skeleTexture = getInvinTime() > 60 ? (
        direction > 0 ? hurtRightTexture : hurtLeftTexture
    ) : skeleTexture;

    skeleTexture = getDead() ? (
        direction > 0 ? deathRightTexture : deathLeftTexture
    ) : skeleTexture;

    setSprIndexMax((!getDead() && getInvinTime() > 60) ? 5 : 10);
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
    Camera::objectSetSprite(this, getInvinTime() > 80);

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