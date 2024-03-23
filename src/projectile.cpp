#include <projectile.h>
#include <map.h>

Projectile::Projectile(SDL_Texture *bTexture, float X, float Y, int hw, int hh, float velX, float velY, int dmg, int age, short harm) :
    Object2D(X, Y, hw, hh, hw, hh),

    // Im old
    bullet_age(age),
    // Harm who?
    harm_player(harm == 1), harm_enemy(harm == -1),
    // Draw and Logic
    bullet_texture(bTexture), vel_x(velX), vel_y(velY)
{}

Projectile::Projectile(SDL_Texture *bTexture, float X, float Y, int hw, int hh, float velX, float velY, int dmg, int age, short harm, bool parry, bool pierece, bool thruWall) :
    Object2D(X, Y, hw, hh, hw, hh, 0, 0, 0, 0),

    // Im old
    bullet_age(age),
    // Harm who?
    harm_player(harm == 1), harm_enemy(harm == -1),
    // Draw and Logic
    bullet_texture(bTexture), vel_x(velX), vel_y(velY),
    // Cool mechanic
    can_parry(parry), can_pierce(pierece), can_wall(thruWall)
{}

Projectile::Projectile(SDL_Texture *bTexture, float X, float Y, int hw, int hh, float velX, float velY, int dmg, int age, short harm, bool parry, bool pierece, bool thruWall, int sim, int sfm) :
    Object2D(X, Y, hw, hh, hw, hh, sim, sfm, 0, 0),

    // Im old
    bullet_age(age),
    // Harm who?
    harm_player(harm == 1), harm_enemy(harm == -1),
    // Draw and Logic
    bullet_texture(bTexture), vel_x(velX), vel_y(velY),
    // Cool mechanic
    can_parry(parry), can_pierce(pierece), can_wall(thruWall)
{}

void Projectile::playerCollision(Player *player)
{   
    // Player Get Hit Oof It hurt
    int colli_x = abs(getX() - player->getHitX());
    int colli_y = abs(getY() - player->getHitY());
    int hit_dist_x = (getWidth() + player->getHitWidth()) / 2;
    int hit_dist_y = (getHeight() + player->getHitHeight()) / 2;

    if (colli_x < hit_dist_x && colli_y < hit_dist_y)
    {
        bullet_dead = !can_pierce && true;
        // Player Hit Animation Here
        player->playerGetHit(bullet_damage);
    }

    // Player Hit The Bullet Back, Get Parried Lmao
    if (can_parry &&
        (player->getCombatTime() || player->getIsADash() || player->getIsGDash()) &&
        (player->getX() < getX() ?  colli_x < player->getCombatHitR() + getWidth() / 2 : 
                                    colli_x < player->getCombatHitL() + getWidth() / 2) &&
        (player->getY() < getY() ?  colli_y < player->getCombatHitU() + getHeight() / 2 : 
                                    colli_y < player->getCombatHitD() + getHeight() / 2))
    {
        harm_player = false;
        harm_enemy = true;

        // std::cout << player->getVelX() << " " << player->getVelY() << "\n";

        vel_parry_x = abs(player->getVelX() * 2) > abs(vel_x) ?
                            player->getVelX() * 2 : -vel_x;
        vel_parry_y = abs(player->getVelY() * 2) > abs(vel_y) ?
                            player->getVelY() * 2 : -vel_y;

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

        if (!can_wall &&
            colli_x < hit_dist_x &&
            colli_y < hit_dist_y)
            bullet_dead =  true;
    }
}

void Projectile::enemyCollision(std::vector<Enemy *> EnemyVec)
{

}

void Projectile::objectCollision(Player *player, Map *map)
{
    if (harm_player) playerCollision(player);
    if (harm_enemy) enemyCollision(map->EnemyVec);
    if (!can_wall) blockCollision(map->BlockVec);
}

void Projectile::projectileAction(SDL_Renderer *renderer, Player* player, Map *map)
{
    if (bullet_age > 0) bullet_age--;
    else bullet_dead = true;

    setX(getX() + vel_x);
    setY(getY() + vel_y);

    if (parry_effect > 0)
    {
        parry_effect--;
        
        if (!parry_effect) 
        {
            vel_x = vel_parry_x;
            vel_y = vel_parry_y;
            Audio::playSFX("res/Audio/SFX/Parry.wav");
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