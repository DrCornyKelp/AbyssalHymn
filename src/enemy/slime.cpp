#include <enemy/slime.h>
#include <map.h>

Slime::Slime(float X, float Y, float limX1, float limX2, short startDir, float scale) :
    Enemy(  X * 64, Y * 64 + 40, 256 * scale, 256 * scale, 58 * scale, 58 * scale,
            80, 72, 7, 20), direction(startDir),
    limLeft(limX1), limRight(limX2)
{}

void Slime::initEnemy()
{
    moveLeftTexture = CFG->loadTexture("assets/EnemySheet/Slime/MoveLeft.png");
    moveRightTexture = CFG->loadTexture("assets/EnemySheet/Slime/MoveRight.png");
    deathTexture = CFG->loadTexture("assets/EnemySheet/Slime/Death.png");

    setHp(20);
    setCollideDamage(20);

    // Random slime color ('v^)
    // srand(time(nullptr));
    color = (rand() % 7) * 72;
}

void Slime::draw(Player *player)
{
    // Frame index shitty bang bang stuff handler
    setSprite();

    // Draw
    SDL_Rect desRect = {Camera::objectDrawX(player, this),
                        Camera::objectDrawY(player, this),
                        hitbox.w, hitbox.h};
    SDL_Rect srcRect = {sprite.si * 80, color, 80, 72};

    if (!getInvinTime()) 
        SDL_SetTextureAlphaMod(slimeTexture, 255);
    SDL_RenderCopy(CFG->RENDERER, slimeTexture, &srcRect, &desRect);
}

void Slime::enemyAI(Map *map)
{
    if (getHp() <= 0 && !getDead())
    {
        setDead(true);
        sprite.si = 0;
        sprite.sfm = 5;
        sprite.sim = 13;
    };

    // The current Texture
    slimeTexture = direction > 0 ?  moveRightTexture:
                                    moveLeftTexture;

    slimeTexture = getDead() ? deathTexture : slimeTexture;

    if (getDead()) return;

    if (hitbox.x > limRight * 64) direction = -1;
    if (hitbox.x < limLeft * 64) direction = 1;
    hitbox.x += direction;

    if (getInvinTime())
    {
        setInvinTime(getInvinTime() - 1);
        SDL_SetTextureAlphaMod(slimeTexture, (getInvinTime() % 15 > 0) ? 200 : 160);
    }
}

void Slime::enemyGetHit(int dmg)
{
    if (getInvinTime()) return;
    setInvinTime(100);
    setHp(getHp() - dmg);
}