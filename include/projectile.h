#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <object2D.h>
#include <vector>

class Map;
class Player;
class Enemy;
class Block;
class Projectile : public Object2D
{
private:
    bool harm_player;
    bool harm_enemy;
    bool can_pierce = false;
    bool can_wall = false;
    bool can_parry = true;

    bool bullet_dead = false;
    bool bullet_parried = false;

    int bullet_age = 0;
    int bullet_damage = 0;
    float vel_x = 0, vel_y = 0;
    float accel_x = 0, accel_y = 0;
    float vel_parry_x = 0, vel_parry_y = 0;

    SDL_Texture *bullet_texture;

    // Fun but unnecessary
    int parry_effect = 0;

public:
    // Standard Projectile (can parry, no wall, no pierce)
    Projectile(SDL_Texture *bTexture, float X, float Y, int hw, int hh, int sw, int sh, float velX, float velY, float accelX, float accelY, int dmg, int age, short harm);
    // Customizable No Animation Projectile
    Projectile(SDL_Texture *bTexture, float X, float Y, int hw, int hh, int sw, int sh, float velX, float velY, float accelX, float accelY, int dmg, int age, short harm, bool parry, bool pierce, bool thruWall);
    // Customizable Yes Animation Projectile
    Projectile(SDL_Texture *bTexture, float X, float Y, int hw, int hh, int sw, int sh, float velX, float velY, float accelX, float accelY, int dmg, int age, short harm, bool parry, bool pierce, bool thruWall, int sim, int sfm);

    // some things
    static float generateRandomFloat();

    // Getter
    bool getBulletDead();
    void setBulletDead(bool dead);
    
    // ================== Deadly =======================
    // Harm the environment (not really, they immortal)
    void blockCollision(std::vector<Block *> BlockVec);
    // Harm you
    void playerCollision(Player *player);
    // Harm them
    void enemyCollision(std::vector<Enemy *> EnemyVec);
    // Harmful in general (lookin at you America)
    void objectCollision(Player *player, Map *map);

    // =================== Velocity ====================
    void projectileAction(SDL_Renderer *renderer, Player* player, Map *map);

    // =================== Update ======================
    void updateProjectile(SDL_Renderer *renderer, Player *player, Map *map);

    // =================== Draw ====-===================
    void draw(SDL_Renderer *renderer, Player *player);
};

#endif