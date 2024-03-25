#include <enemy/slime.h>
#include <player.h>
#include <map.h>

Slime::Slime(float X, float Y, float limX1, float limX2, short startDir, float scale) :
    Enemy(X * 64, Y * 64, 256 * scale, 256 * scale, 58 * scale, 58 * scale, 7, 20), direction(startDir),
    limLeft(limX1), limRight(limX2)
{}

void Slime::initEnemy(SDL_Renderer *renderer)
{
    moveLeftSprite = new Sprite(80, 72, 1, "res/EnemySheet/Slime/MoveLeft.png");
    moveLeftSprite->setTexture(Sprite::loadTexture(renderer, moveLeftSprite->getSpritePath()));

    moveRightSprite = new Sprite(80, 72, 1, "res/EnemySheet/Slime/MoveRight.png");
    moveRightSprite->setTexture(Sprite::loadTexture(renderer, moveRightSprite->getSpritePath()));

    deathSprite = new Sprite(80, 72, 1, "res/EnemySheet/Slime/Death.png");
    deathSprite->setTexture(Sprite::loadTexture(renderer, deathSprite->getSpritePath()));

    bulletSprite = new Sprite(16, 16, 1, "res/EnemySheet/Slime/Bullet.png");
    bulletSprite->setTexture(Sprite::loadTexture(renderer, bulletSprite->getSpritePath()));

    setHp(20);
    setCollideDamage(20);

    // Random slime color ('v^)
    // srand(time(nullptr));
    color = (rand() % 7) * 72;
}

void Slime::draw(SDL_Renderer *renderer, Player *player)
{
    // Outside seeable? unrender
    if (Camera::objectOutBound(player, this))
        return;
    // Frame index shitty bang bang stuff handler
    Camera::objectSetSprite(this);

    // Draw
    double cam_scale = player->getCameraScale();
    SDL_Rect desRect = {Camera::objectDrawX(player, this),
                        Camera::objectDrawY(player, this),
                        int(getWidth() * cam_scale),
                        int(getHeight() * cam_scale)};
    SDL_Rect srcRect = {getSprIndex() * 80, color, 80, 72};

    if (!getInvinTime()) 
        SDL_SetTextureAlphaMod(slimeTexture, 255);
    SDL_RenderCopy(renderer, slimeTexture, &srcRect, &desRect);
}

void Slime::enemyAI(Player *player, Map *map)
{
    if (getX() > limRight * 64) direction = -1;
    if (getX() < limLeft * 64) direction = 1;
    setX(getX() + direction);

    if (getInvinTime())
    {
        setInvinTime(getInvinTime() - 1);
        SDL_SetTextureAlphaMod(slimeTexture, (getInvinTime() % 15 > 0) ? 200 : 160);
    }

    if (getHp() <= 0) 
    {
        setDead(true);
        setSprIndex(0);
        setSprFrameMax(5);
        setSprIndexMax(13);
    };

    if (time < 500) time++;
    else
    {
        time = rand() % 50;

        float colli_vx = player->getX() - getX();
        float colli_vy = player->getY() - getY();

        float vel_x = colli_vx > 0 ? 1 : -1;
        float vel_y = abs(colli_vy / colli_vx) * (colli_vy > 0 ? 1 : -1); 

        map->ProjectileVec.push_back(
        new Projectile(bulletSprite->getTexture(), getX(), getY(), 16, 16, 16, 16,
                        vel_x * 20, vel_y * 20, 0, 0, 15, 1000, 1)
        );
        map->ProjectileVec.push_back(
        new Projectile(bulletSprite->getTexture(), getX(), getY(), 16, 16, 16, 16,
                        vel_x * 20, vel_y * 20 + 1, 0, 0, 15, 1000, 1)
        );
        map->ProjectileVec.push_back(
        new Projectile(bulletSprite->getTexture(), getX(), getY(), 16, 16, 16, 16,
                        vel_x * 20, vel_y * 20 - 1, 0, 0, 15, 1000, 1)
        );
    }

    // The current Texture
    slimeTexture = direction > 0 ?  moveRightSprite->getTexture():
                                    moveLeftSprite->getTexture();

    slimeTexture = getDead() ? deathSprite->getTexture() : slimeTexture;
}

void Slime::enemyPlayerCollision(Player *player)
{

}

void Slime::enemyGetHit(int dmg)
{
    if (getInvinTime()) return;
    setInvinTime(100);
    setHp(getHp() - dmg);
}