#include <projectile.h>
#include <map.h>

float Projectile::generateRandomFloat() {
    srand((unsigned) time(NULL));
	float random = rand() % 100 - 50;
    return random / 50;
}

Projectile::Projectile(SDL_Texture *bTexture, float X, float Y, int hw, int hh, int sw, int sh, float velX, float velY, float accelX, float accelY, int dmg, int age, short harm) :
    Object2D(X, Y, sw, sh, hw, hh, 0, 0, 0, 0),

    // Bullet properties
    bullet_age(age), bullet_damage(dmg), bullet_texture(bTexture),
    // Harm who?
    harm_player(harm == 1), harm_enemy(harm == -1)
{
    setVelX(velX); setVelY(velY);
    setAccelX(accelX); setAccelY(accelY);
}

Projectile::Projectile(SDL_Texture *bTexture, float X, float Y, int hw, int hh, int sw, int sh, float velX, float velY, float accelX, float accelY, int dmg, int age, short harm, bool parry, bool pierece, bool thruWall) :
    Object2D(X, Y, sw, sh, hw, hh, 0, 0, 0, 0),

    // Bullet properties
    bullet_age(age), bullet_damage(dmg), bullet_texture(bTexture),
    // Harm who?
    harm_player(harm == 1), harm_enemy(harm == -1),
    // Cool mechanic
    can_parry(parry), can_pierce(pierece), can_wall(thruWall)
{
    setVelX(velX); setVelY(velY);
    setAccelX(accelX); setAccelY(accelY);
}

Projectile::Projectile(SDL_Texture *bTexture, float X, float Y, int hw, int hh, int sw, int sh, float velX, float velY, float accelX, float accelY, int dmg, int age, short harm, bool parry, bool pierece, bool thruWall, int sim, int sfm) :
    Object2D(X, Y, sw, sh, hw, hh, sim, sfm, 0, 0),

    // Im old
    bullet_age(age), bullet_damage(dmg), bullet_texture(bTexture),
    // Harm who?
    harm_player(harm == 1), harm_enemy(harm == -1),
    // Cool mechanic
    can_parry(parry), can_pierce(pierece), can_wall(thruWall)
{
    setVelX(velX); setVelY(velY);
    setAccelX(accelX); setAccelY(accelY);

    std::cout << accelY << "\n";
}

void Projectile::playerCollision(Player *player)
{   
    // Player Get Hit Oof It hurt
    int colli_x = abs(getX() - player->getHitX());
    int colli_y = abs(getY() - player->getHitY());
    int hit_dist_x = (getHitWidth() + player->getHitWidth()) / 2;
    int hit_dist_y = (getHitHeight() + player->getHitHeight()) / 2;

    if (harm_player && colli_x < hit_dist_x && colli_y < hit_dist_y)
    {
        bullet_dead = !can_pierce && true;
        // Player Hit Animation Here
        player->playerGetHit(bullet_damage);
    }

    // Player Hit The Bullet Back, Get Parried Lmao
    // Interesting mechanic, player could literally parry
    //              their own bullet lmao
    if (can_parry && !bullet_parried &&
        (player->getCombatTime() && !player->getIsADash() && !player->getIsGDash()) &&
        (player->getX() < getX() ?  colli_x < player->getCombatHitR() + getHitWidth() / 2 : 
                                    colli_x < player->getCombatHitL() + getHitWidth() / 2) &&
        (player->getY() < getY() ?  colli_y < player->getCombatHitU() + getHitHeight() / 2 : 
                                    colli_y < player->getCombatHitD() + getHitHeight() / 2))
    {
        bullet_parried = true;
        harm_player = false;
        harm_enemy = true;

        vel_parry_x = player->getActRight() ? 10 : -10;
        vel_parry_y = player->getVelY() + generateRandomFloat() * player->getCombatParryError();

        // Bullet Stop Motion
        setVelX(0); setVelY(0);
        setAccelX(0); setAccelY(0);

        // Other stuff
        player->setCombatDelay(100);
        parry_effect = player->getCombatTime();
    }
}

void Projectile::blockCollision(std::vector<Block *> BlockVec)
{
    for (Block *block : BlockVec)
    {
        if (block->getGoThru() || block->getSeeThru()) continue;

        int colli_x = abs(getX() - block->getX());
        int colli_y = abs(getY() - block->getY());
        int hit_dist_x = (getWidth() + block->getWidth()) / 2;
        int hit_dist_y = (getHeight() + block->getHeight()) / 2;

        if (colli_x < hit_dist_x &&
            colli_y < hit_dist_y)
        {
            bullet_dead = true;
            return;
        }
    }
}

void Projectile::enemyCollision(std::vector<Enemy *> EnemyVec)
{
    // Enemy Get Hit Oof It hurt

    for (Enemy *enemy : EnemyVec)
    {
        int colli_x = abs(getX() - enemy->getX());
        int colli_y = abs(getY() - enemy->getY());
        int hit_dist_x = (getHitWidth() + enemy->getHitWidth()) / 2;
        int hit_dist_y = (getHitHeight() + enemy->getHitHeight()) / 2;

        if (colli_x < hit_dist_x && colli_y < hit_dist_y)
        {
            bullet_dead = !can_pierce && true;
            // Enemy Hit Animation Here
            enemy->enemyGetHit(bullet_damage);
        }       
    }

    // NGL might actually make enemy parry
    // that would be really insane but hey!
}

void Projectile::projectileCollision(Player *player, Map *map)
{
    playerCollision(player);
    if (harm_enemy) enemyCollision(map->EnemyVec);
    if (!can_wall) blockCollision(map->BlockVec);
}

void Projectile::projectileAction(SDL_Renderer *renderer, Player* player, Map *map)
{
    if (bullet_age > 0) bullet_age--;
    else bullet_dead = true;

    setX(getX() + getVelX());
    setY(getY() + getVelY());
    setVelX(getVelX() + getAccelX());
    setVelY(getVelY() + getAccelY());

    if (parry_effect > 0)
    {
        parry_effect--;
        
        if (!parry_effect) 
        {
            setSprFrameMax(getSprFrameMax() / 3);
            setVelX(vel_parry_x);
            setVelY(vel_parry_y);
        }
    }
}

void Projectile::updateProjectile(SDL_Renderer *renderer, Player *player, Map *map)
{
    projectileAction(renderer, player, map);
    projectileCollision(player, map);
}

void Projectile::draw(SDL_Renderer *renderer, Player *player)
{   
    // Only render if box is in sight
    if (Camera::objectOutBound(player, this))
        return;
    // Set animation
    Camera::objectSetSprite(this);

    // Draw
    float cam_scale = player->getCameraScale();
    SDL_Rect desRect = {Camera::objectDrawX(player, this),
                        Camera::objectDrawY(player, this),
                        int(getWidth() * cam_scale), int(getHeight() * cam_scale)};
    SDL_Rect srcRect;
    if (getSprIndexMax() > 0) srcRect = {getSprIndex() * getWidth(), 0, getWidth(), getHeight()};
    else srcRect = {0, 0, getWidth(), getHeight()};

    SDL_RenderCopy(renderer, bullet_texture, &srcRect, &desRect);
}

// Getter
bool Projectile::getBulletDead()
{
    return bullet_dead;
}
bool Projectile::getBulletParried()
{
    return bullet_parried;
}

// Setter
void Projectile::setBulletDead(bool dead)
{
    bullet_dead = dead;
}