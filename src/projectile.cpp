#include <projectile.h>
#include <map.h>

float Projectile::generateRandomFloat() {
    srand((unsigned) time(NULL));
	float random = rand() % 100 - 50;
    return random / 50;
}

Projectile::~Projectile()
{ SDL_DestroyTexture(proj_texture); }

Projectile::Projectile( string0D pPath,
                        float X, float Y, int hw, int hh, int sw, int sh,
                        float velX, float velY, float accelX, float accelY,
                        int dmg, int age, short harm) :
    Object2D(X, Y, sw, sh, hw, hh),
    // Bullet properties
    bullet_age(age), bullet_damage(dmg), proj_path(pPath),
    // Harm who?
    harm_player(harm != -1), harm_enemy(harm != 1)
{
    proj_texture = loadTexture(proj_path);
    setVelX(velX); setVelY(velY);
    setAccelX(accelX); setAccelY(accelY);
}

Projectile::Projectile( string0D pPath,
                        float X, float Y, int hw, int hh, int sw, int sh,
                        float velX, float velY, float accelX, float accelY,
                        int dmg, int age, short harm,
                        bool parry, bool pierece, bool thruWall) :
    Object2D(X, Y, sw, sh, hw, hh),
    // Bullet properties
    bullet_age(age), bullet_damage(dmg), proj_path(pPath),
    // Harm who?
    harm_player(harm != -1), harm_enemy(harm != 1),
    // Cool mechanic
    can_parry(parry), can_pierce(pierece), can_wall(thruWall)
{
    proj_texture = loadTexture(proj_path);
    setVelX(velX); setVelY(velY);
    setAccelX(accelX); setAccelY(accelY);
}

Projectile::Projectile( string0D pPath,
                        float X, float Y, int hw, int hh, int sw, int sh,
                        float velX, float velY, float accelX, float accelY,
                        int dmg, int age, short harm,
                        bool parry, bool pierece, bool thruWall,
                        int sim, int sfm) :
    Object2D(X, Y, sw, sh, hw, hh, sw, sh, sim, sfm, 0, 0),
    // Im old
    bullet_age(age), bullet_damage(dmg), proj_path(pPath),
    // Harm who?
    harm_player(harm != -1), harm_enemy(harm != 1),
    // Cool mechanic
    can_parry(parry), can_pierce(pierece), can_wall(thruWall)
{
    proj_texture = loadTexture(proj_path);
    setVelX(velX); setVelY(velY);
    setAccelX(accelX); setAccelY(accelY);
}

void Projectile::playerCollision(Player *player, Map *map)
{   
    // Player Get Hit Oof It hurt

    if (harm_player && Collision::playerCollision(player, this))
    {
        bullet_dead = !can_pierce && true;
        // Player Hit Animation Here
        player->playerGetHit(map, bullet_damage);
    }

    // Player Hit The Bullet Back, Get Parried Lmao
    // Interesting mechanic, player could literally parry
    //              their own bullet lmao
    if (can_parry && !bullet_parried &&
        (player->combat.time &&
        !player->a_dash.frame &&
        !player->g_dash.frame) &&
        Collision::playerCombatCollision(player, this))
    {
        bullet_parried = true;
        harm_player = false;
        harm_enemy = true;

        vel_parry_x = player->draw_prop.right ? 10 : -10;
        vel_parry_y = player->getVelY() + generateRandomFloat() * player->combat.parry_error;

        // Bullet Stop Motion
        setVelX(0); setVelY(0);
        setAccelX(0); setAccelY(0);

        // Other stuff
        player->combat.delay = 100;
        parry_effect = player->combat.time;
    }
}

void Projectile::blockCollision(Block *block)
{
    // Transparent/Go Through block
    if (block->isType(2) || block->isType(-1)) return;

    int hit_dist_y = (getHitHeight() + block->getHeight()) / 2;

    if (Collision::objectCollision(this, block) &&
        // Different logic for bridge block
        (!block->isType(3) || (
            getVelY() <= 0 &&
            getY() > block->getY() + hit_dist_y + getVelY() - 2
        )))
    {
        bullet_dead = true;
        return;
    }
}

void Projectile::enemyCollision(Map *map)
{
    // Enemy Get Hit Oof It hurt

    for (Enemy *enemy : map->EnemyVec)
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
    playerCollision(player, map);
    // Enemy
    if (harm_enemy) enemyCollision(map);
    // Block
    if (!can_wall) 
    {
        for (Block *block : map->BlockMainVec)
            blockCollision(block);
        for (Block *block : map->BlockBackVec)
            blockCollision(block);
    };
}

void Projectile::projectileAction(Player* player, Map *map)
{
    if (bullet_age > 0) bullet_age--;
    else bullet_dead = true;

    objectStandardMovement();

    if (parry_effect > 0)
    {
        parry_effect--;
        
        if (!parry_effect)
        {
            map->ParticleFrontVec.push_back(new ParticleEffect(
                loadTexture(
                    "res/ParticleSheet/BulletParry.png"
                ),
                getX(), getY(), 150, 150,
                64, 64, 7, 3, 0
            ));

            setSprFrameMax(getSprFrameMax() / 3);
            setVelX(vel_parry_x);
            setVelY(vel_parry_y);
        }
    }
}

void Projectile::updateProjectile(Player *player, Map *map)
{
    projectileAction(player, map);
    projectileCollision(player, map);

    if (bullet_dead)
        map->ParticleFrontVec.push_back(new ParticleEffect(
            loadTexture("res/ParticleSheet/Explode.png"),
            getX(), getY(), 200, 200,
            100, 100, 10, 7, 3, 0
        ));
}

void Projectile::draw(Player *player)
{   
    // Only render if box is in sight
    if (Camera::objectIgnore(player, this))
        return;
    // Set animation
    objectSetSprite();

    // Draw
    SDL_Rect desRect = {Camera::objectDrawX(player, this),
                        Camera::objectDrawY(player, this),
                        getWidth(), getHeight()};
    SDL_Rect srcRect;
    if (getSprIndexMax() > 0) srcRect = {getSprIndex() * getWidth(), 0, getWidth(), getHeight()};
    else srcRect = {0, 0, getWidth(), getHeight()};

    SDL_RenderCopy(CFG->RENDERER, proj_texture, &srcRect, &desRect);
}

bool Projectile::getBulletDead() { return bullet_dead; }
void Projectile::setBulletDead(bool dead) { bullet_dead = dead; }
bool Projectile::getBulletParried() { return bullet_parried; }