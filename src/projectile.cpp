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
    Object2D({X, Y, float(sw), float(sh), hw, hh}),
    // Bullet properties
    bullet_age(age), bullet_damage(dmg), proj_path(pPath),
    // Harm who?
    harm_player(harm != -1), harm_enemy(harm != 1)
{
    proj_texture = CFG->loadTexture(proj_path);
    vel.x = velX; vel.y = velY;
    accel.x = accelX; accel.y = accelY;
}

Projectile::Projectile( string0D pPath,
                        float X, float Y, int hw, int hh, int sw, int sh,
                        float velX, float velY, float accelX, float accelY,
                        int dmg, int age, short harm,
                        bool parry, bool pierece, bool thruWall) :
    Object2D({X, Y, float(sw), float(sh), hw, hh}),
    // Bullet properties
    bullet_age(age), bullet_damage(dmg), proj_path(pPath),
    // Harm who?
    harm_player(harm != -1), harm_enemy(harm != 1),
    // Cool mechanic
    can_parry(parry), can_pierce(pierece), can_wall(thruWall)
{
    proj_texture = CFG->loadTexture(proj_path);
    vel.x = velX; vel.y = velY;
    accel.x = accelX; accel.y = accelY;
}

Projectile::Projectile( string0D pPath,
                        float X, float Y, int hw, int hh, int sw, int sh,
                        float velX, float velY, float accelX, float accelY,
                        int dmg, int age, short harm,
                        bool parry, bool pierece, bool thruWall,
                        int sim, int sfm) :
    Object2D(
        {X, Y, float(sw), float(sh), hw, hh},
        {sw, sh, sim, sfm}
    ),
    // Im old
    bullet_age(age), bullet_damage(dmg), proj_path(pPath),
    // Harm who?
    harm_player(harm != -1), harm_enemy(harm != 1),
    // Cool mechanic
    can_parry(parry), can_pierce(pierece), can_wall(thruWall)
{
    proj_texture = CFG->loadTexture(proj_path);
    vel.x = velX; vel.y = velY;
    accel.x = accelX; accel.y = accelY;
}

void Projectile::playerCollision(Map *map, Player *player)
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
        harm_player = true;
        harm_enemy = true;

        vel_parry_x = player->psprite.right ? 10 : -10;
        vel_parry_y = player->vel.y + generateRandomFloat() * player->combat.parry_error;

        // Bullet Stop Motion
        vel.x = 0;
        vel.y = 0;
        accel.x = 0;
        accel.y = 0;

        // Other stuff
        player->combat.delay = 100;
        parry_effect = player->combat.time;
    }
}

void Projectile::blockCollision(Block *block)
{
    // Transparent/Go Through block
    if (block->type == 2 || block->type == -1) return;

    int hit_dist_y = (hitbox.h + block->hitbox.h) / 2;

    if (Collision::objectCollision(this, block) &&
        // Different logic for bridge block
        (!block->type == 3 || (
            vel.y <= 0 &&
            hitbox.y > block->hitbox.y + hit_dist_y + vel.y - 2
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
        int colli_x = abs(hitbox.x - enemy->hitbox.x);
        int colli_y = abs(hitbox.y - enemy->hitbox.y);
        int hit_dist_x = (hitbox.w + enemy->hitbox.w) / 2;
        int hit_dist_y = (hitbox.h + enemy->hitbox.h) / 2;

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

void Projectile::projectileCollision(Map *map)
{
    for (Player *player : map->MULTI->Players)
        playerCollision(map, player);
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

void Projectile::projectileAction(Map *map)
{
    if (bullet_age > 0) bullet_age--;
    else bullet_dead = true;

    objectStandardMovement();

    if (parry_effect > 0)
    {
        parry_effect--;
        
        if (!parry_effect)
        {
            map->appendParticle(new ParticleEffect(
                CFG->loadTexture(
                    "assets/ParticleSheet/BulletParry.png"
                ),
                hitbox.x, hitbox.y, 150, 150,
                64, 64, 7, 3, 0
            ), 1);

            sprite.sfm /= 3;
            vel.x = vel_parry_x;
            vel.y = vel_parry_y;
        }
    }
}

void Projectile::updateProjectile(Map *map)
{
    // Update Logic
    projectileAction(map);
    projectileCollision(map);

    // Drawing properties
    desRect = {
        Camera::objectDrawX(map->MULTI->MAIN, this),
        Camera::objectDrawY(map->MULTI->MAIN, this),
        int(hitbox.w), int(hitbox.h)
    };

    if (sprite.sim > 0)
        srcRect = {sprite.si * int(hitbox.w), 0, int(hitbox.w), int(hitbox.h)};
    else
        srcRect = {0, 0, int(hitbox.w), int(hitbox.h)};

    setSprite();

    // Bullet Died :(
    if (bullet_dead)
        map->appendParticle(new ParticleEffect(
            CFG->loadTexture("assets/ParticleSheet/Explode.png"),
            hitbox.x, hitbox.y, 200, 200,
            100, 100, 10, 7, 3, 0
        ), 1);
}

void Projectile::draw(Player *player)
{
    if (Camera::outOfBound(desRect) ||
        Camera::outOfCam(player, this))
        return;

    SDL_RenderCopy(CFG->RENDERER, proj_texture, &srcRect, &desRect);
}

bool Projectile::getBulletDead() { return bullet_dead; }
void Projectile::setBulletDead(bool dead) { bullet_dead = dead; }
bool Projectile::getBulletParried() { return bullet_parried; }