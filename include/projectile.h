#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <object2D.h>

#define Projectile1D std::vector<Projectile*>

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
    float vel_parry_x = 0, vel_parry_y = 0;

    std::string proj_path;
    SDL_Texture *proj_texture;

    // Fun but unnecessary
    int parry_effect = 0;

public:
    ~Projectile();
    // Standard Projectile (can parry, no wall, no pierce)
    Projectile(std::string pPath, float X, float Y, int hw, int hh, int sw, int sh, float velX, float velY, float accelX, float accelY, int dmg, int age, short harm);
    // Customizable No Animation Projectile
    Projectile(std::string pPath, float X, float Y, int hw, int hh, int sw, int sh, float velX, float velY, float accelX, float accelY, int dmg, int age, short harm, bool parry, bool pierce, bool thruWall);
    // Customizable Yes Animation Projectile
    Projectile(std::string pPath, float X, float Y, int hw, int hh, int sw, int sh, float velX, float velY, float accelX, float accelY, int dmg, int age, short harm, bool parry, bool pierce, bool thruWall, int sim, int sfm);

    // some things
    static float generateRandomFloat();

    // Getter
    bool getBulletDead();
    bool getBulletParried();
    // Setter
    void setBulletDead(bool dead);
    
    // ================== Deadly =======================
    // Harm the environment (not really, they immortal)
    void blockCollision(Block *block);
    // Harm you
    void playerCollision(Player *player, Map *map);
    // Harm them
    void enemyCollision(Map *map);
    // Harmful in general (lookin at you America)
    void projectileCollision(Player *player, Map *map);

    // =================== Velocity ====================
    void projectileAction(Player* player, Map *map);

    // =================== Update ======================
    void updateProjectile(Player *player, Map *map);

    // =================== Draw ====-===================
    void draw(Player *player);
};

#endif