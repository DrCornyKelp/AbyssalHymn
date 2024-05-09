#include <enemy/slime.h>
#include <map.h>

Slime::Slime(float X, float Y, float limX1, float limX2, short startDir, float scale) :
    Enemy(  X * 64, Y * 64 + 40, 256 * scale, 256 * scale, 58 * scale, 58 * scale,
            80, 72, 7, 20), direction(startDir),
    limLeft(limX1), limRight(limX2)
{}

void Slime::initEnemy()
{
    moveLeftTexture = loadTexture("res/EnemySheet/Slime/MoveLeft.png");
    moveRightTexture = loadTexture("res/EnemySheet/Slime/MoveRight.png");
    deathTexture = loadTexture("res/EnemySheet/Slime/Death.png");

    setHp(20);
    setCollideDamage(20);

    // Random slime color ('v^)
    // srand(time(nullptr));
    color = (rand() % 7) * 72;
}

void Slime::draw(Player *player)
{
    // Outside seeable? unrender
    if (Camera::objectIgnore(player, this))
        return;
    // Frame index shitty bang bang stuff handler
    objectSetSprite();

    // Draw
    SDL_Rect desRect = {Camera::objectDrawX(player, this),
                        Camera::objectDrawY(player, this),
                        getWidth(), getHeight()};
    SDL_Rect srcRect = {getSprIndex() * 80, color, 80, 72};

    if (!getInvinTime()) 
        SDL_SetTextureAlphaMod(slimeTexture, 255);
    SDL_RenderCopy(CFG->RENDERER, slimeTexture, &srcRect, &desRect);
}

void Slime::enemyAI(Map *map)
{
    if (getHp() <= 0 && !getDead())
    {
        setDead(true);
        setSprIndex(0);
        setSprFrameMax(5);
        setSprIndexMax(13);
    };

    // The current Texture
    slimeTexture = direction > 0 ?  moveRightTexture:
                                    moveLeftTexture;

    slimeTexture = getDead() ? deathTexture : slimeTexture;

    if (getDead()) return;

    if (getX() > limRight * 64) direction = -1;
    if (getX() < limLeft * 64) direction = 1;
    setX(getX() + direction);

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