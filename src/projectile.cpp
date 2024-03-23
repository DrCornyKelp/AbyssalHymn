#include <projectile.h>
#include <map.h>

Projectile::Projectile(SDL_Texture *bTexture, float X, float Y, int hw, int hh, int sw, int sh, float velX, float velY, float accelX, float accelY, int dmg, int age, short harm) :
    Object2D(X, Y, sw, sh, hw, hh, 0, 0, 0, 0),

    // Bullet properties
    bullet_age(age), bullet_damage(dmg), bullet_texture(bTexture),
    // Harm who?
    harm_player(harm == 1), harm_enemy(harm == -1),
    // Draw and Logic
    vel_x(velX), vel_y(velY), accel_x(accelX), accel_y(accelY)
{}

float Projectile::generateRandomFloat() {
    srand((unsigned) time(NULL));
	float random = rand() % 100 - 50;
    return random / 50;
}

Projectile::Projectile(SDL_Texture *bTexture, float X, float Y, int hw, int hh, int sw, int sh, float velX, float velY, float accelX, float accelY, int dmg, int age, short harm, bool parry, bool pierece, bool thruWall) :
    Object2D(X, Y, sw, sh, hw, hh, 0, 0, 0, 0),

    // Bullet properties
    bullet_age(age), bullet_damage(dmg), bullet_texture(bTexture),
    // Harm who?
    harm_player(harm == 1), harm_enemy(harm == -1),
    // Speed and stuff
    vel_x(velX), vel_y(velY), accel_x(accelX), accel_y(accelY),
    // Cool mechanic
    can_parry(parry), can_pierce(pierece), can_wall(thruWall)
{}

Projectile::Projectile(SDL_Texture *bTexture, float X, float Y, int hw, int hh, int sw, int sh, float velX, float velY, float accelX, float accelY, int dmg, int age, short harm, bool parry, bool pierece, bool thruWall, int sim, int sfm) :
    Object2D(X, Y, sw, sh, hw, hh, sim, sfm, 0, 0),

    // Im old
    bullet_age(age), bullet_damage(dmg), bullet_texture(bTexture),
    // Harm who?
    harm_player(harm == 1), harm_enemy(harm == -1),
    // Draw and Logic
    vel_x(velX), vel_y(velY), accel_x(accelX), accel_y(accelY),
    // Cool mechanic
    can_parry(parry), can_pierce(pierece), can_wall(thruWall)
{}

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

        vel_parry_x = player->getActRight() ? 5 : -5;
        std::cout << generateRandomFloat() << "\n";
        vel_parry_y = player->getVelY() + generateRandomFloat() * player->getCombatParryError();

        // Bullet Stop Motion
        vel_x *= .2;
        vel_y *= .2;
        accel_x = 0;
        accel_y = 0;

        // Other stuff
        player->setCombatDelay(150);
        parry_effect = player->getCombatTime();
    }
}

void Projectile::blockCollision(std::vector<Block *> BlockVec)
{
    for (Block *block : BlockVec)
    {
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
            // Player Hit Animation Here
            enemy->enemyGetHit(bullet_damage);
        }       
    } 
    

    // NGL miggt actually make enemy parry
    // that would be really insane but hey!
}

void Projectile::objectCollision(Player *player, Map *map)
{
    playerCollision(player);
    if (harm_enemy) enemyCollision(map->EnemyVec);
    if (!can_wall) blockCollision(map->BlockVec);
}

void Projectile::projectileAction(SDL_Renderer *renderer, Player* player, Map *map)
{
    if (bullet_age > 0) bullet_age--;
    else bullet_dead = true;

    setX(getX() + vel_x);
    setY(getY() + vel_y);
    vel_x += accel_x;
    vel_y += accel_y;

    if (parry_effect > 0)
    {
        parry_effect--;
        
        if (!parry_effect) 
        {
            vel_x = vel_parry_x;
            vel_y = vel_parry_y;
            // Audio::playSFX("res/Audio/SFX/Parry.wav");
            SDL_Delay(100);
        }
    }
}

void Projectile::updateProjectile(SDL_Renderer *renderer, Player *player, Map *map)
{
    projectileAction(renderer, player, map);
    objectCollision(player, map);
}

void Projectile::draw(SDL_Renderer *renderer, Player *player)
{   
    // (Ok im pretty sure these value are being highly reused XD)
    // (Might make a method of this later)
    // Camera is a piece of shit
    int rel_x = player->getFocusX() ? player->getOffsetX() + getX() - player->getX() : getX();
    int rel_y = player->getFocusY() ? player->getOffsetY() + getY() - player->getY() : getY();

    // Frame index shitty bang bang stuff handler
    if (getSprIndexMax())
    {
        if (getSprFrame() < getSprFrameMax())
        {
            setSprFrame(getSprFrame() + 1);
        }
        else
        {
            setSprFrame(0);
            setSprIndex(getSprIndex() + 1);
        }
        if (getSprIndex() >= getSprIndexMax())
            setSprIndex(0);
    }

    int colli_x = abs(player->getX() - getX());
    int colli_y = abs(player->getY() - getY());

    // Only render if box is in sight
    if (colli_x - getWidth() / 2 > Game::WIDTH ||
        colli_y - getHeight() / 2 > Game::HEIGHT
    ) return;

    SDL_Rect desRect = {rel_x - getWidth() / 2, Game::HEIGHT - rel_y - getHeight() / 2, getWidth(), getHeight()};
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

// Setter
void Projectile::setBulletDead(bool dead)
{
    bullet_dead = dead;
}