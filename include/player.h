#ifndef PLAYER_H
#define PLAYER_H

#include "input.h"
#include "block.h"
#include "enemy.h"

typedef void (*FocusFunc)(Player *);

class Map;
class Player : public Object2D
{
private:
    // Elden ring
    int hp = 100;
    int hp_max = 100;
    int mp = 100;
    int mp_max = 100;

    // Moveset availability
    bool can_move = true;
    bool can_jump = false;
    bool can_crawl = false;
    bool can_g_dash = false;
    bool can_a_dash = false;
    bool can_hug_wall = false;

    // Buff Effect
    float buff_move = 1;
    float buff_jump = 1;
    float buff_combat_speed = 1;
    float buff_combat_damage = 1;

    int buff_move_time = 0;
    int buff_jump_time = 0;
    int buff_combat_speed_time = 0;
    int buff_combat_damage_time = 0;

    // Condition
    bool on_ice = false;
    bool on_ground = false;
    bool hug_wall_left = false;
    bool hug_wall_right = false;

    // Ground movement
    float vel_x = 0;
    float vel_x_max = 5;
    float vel_x_max_ground = 7;
    float vel_x_max_air = 6;
    float accel_x = 0.1;
    float accel_x_ground = 0.1;
    float accel_x_ice = 0.06;

    // Crawling
    bool crawl = false;
    bool crawl_lock = false;
    float vel_crawl = .8;
    int hit_offset_x = 0;
    int hit_offset_y = 0;

    // Decelleration
    // 0: none, -1: LEFT, 1: RIGHT
    int decel_x = 0; 

    // "Airborne" movement
    int air_cur = 0;
    int air_max = 2;

    // Jumping
    bool jump_keyhold = false;
    float vel_y = 0;
    float vel_terminal = 10;
    float accel_y = 0.1;
    float accel_hold = 0.1;
    float accel_tap = 0.2;
    // SUPER JUMPING
    int jump_super = 0;
    int jump_super_max = 80;
    // Ceiling Knockout
    int ceiling_knockout = 0;
    int ceiling_knockout_delay = 50;

    // Air dash
    bool a_dash = false;
    // Frame
    int a_dash_frame = 0;
    int a_dash_frame_max = 0;
    int a_dash_frame_normal = 20;
    int a_dash_frame_weapon = 15;
    // Delay
    int a_dash_delay = 0;
    int a_dash_delay_max = 0;
    int a_dash_delay_normal = 40;
    int a_dash_delay_weapon = 100;

    // Ground Dash
    bool g_dash = false;
    // Velo
    int g_dash_vel = 0;
    int g_dash_vel_normal = 10;
    int g_dash_vel_weapon = 8;
    // Frame
    int g_dash_frame = 0;
    int g_dash_frame_max = 0;
    int g_dash_frame_normal = 45;
    int g_dash_frame_weapon = 35;
    // Delay
    int g_dash_delay = 0;
    int g_dash_delay_max = 0;
    int g_dash_delay_normal = 60;
    int g_dash_delay_weapon = 120;

    // ================== Combat ===================

    // Invincibility (is when you are god)
    int invincible_time = 0;
    // Invurnable time (is when you get hurt)
    int invurnable_time = 0;
    int invurnable_time_max = 150;

    // Weapon handler
    bool weapon_equip = true;
    int weapon_equip_frame = 0; // Only use for drawing
    int weapon_equip_delay = 0;
    int weapon_equip_delay_max = 200;

    // Time the atk exist
    float combat_time = 0; 
    // Time you perform follow up
    float combat_combo_time = 0;
    // The ...well, delay lmao
    float combat_delay = 0; 
    // The ...umm, are you blind
    bool combat_keytap = false;
    bool combat_keyhold = false;
    int combat_keytime = 0;
    bool combat_keyhold_time = 0;
    // Combat numbers and stuff
    int combat_charge_time = 0;
    int combat_damage = 13;
    int combat_index = 0;
    int combat_hit_up = 0;
    int combat_hit_down = 0;
    int combat_hit_left = 0;
    int combat_hit_right = 0;
    float combat_parry_error = 0;

    // Combat Projectile
    bool jelly_keyhold = false;

    // ================= DRAWING ====================
    // Le Sprite itself (do not touch)
    SDL_Texture *playerCurrentTexture;
    Sprite *PlayerLeft;
    Sprite *PlayerRight;
    Sprite *PlayerLeftWeapon;
    Sprite *PlayerRightWeapon;
    Sprite *PlayerSquid;
    
    // Action indexing and stuff idk
    int act_index = 0;
    bool act_right = true;

    // Sprite handler
    int sprite_alpha = 255;
    bool sprite_end_lock = false;
    int sprite_size = 64;

    // EXTREMELY COMPLICATED CAMERA
    int offset_mid_x = 0;
    int offset_mid_y = 0;
    bool unfocus_x = 0;
    bool unfocus_y = 0;
    int unfocus_offset_x = 0;
    int unfocus_offset_y = 0;
    double camera_scale = 0.9375; // 0.625
    FocusFunc focus_function;

    int earth_quake = 0;
    int earth_quake_direction = 1;

    // ====== DEVELOPER VALUES ======
    Sprite *hitbox;
    Sprite *combatbox;

    bool godmode = false;
    bool godmode_hold;

    bool grid = false;
    bool grid_hold;

public:
    // Constructor
    Player(float X = 640, float Y = 400, int w = 128, int h = 128, int hw = 0, int hh = 0, int sim = 2, int sfm = 20, int si = 0, int sf = 0);
    void initPlayer(SDL_Renderer *renderer);

    void setVelX(float X);
    void setVelY(float Y);
    float getVelX();
    float getVelY();
    int getHitX();
    int getHitY();
    
    void setSprite(int m_index, int m_frame);
    void setSpriteAlpha(int alpha);
    void setAct(int index, bool right);
    void setEndLock(bool lock);

    void setCombatDelay(float delay);
    void setInvincibleTime(int time);

    // Getter
    
    int getActIndex();
    bool getActRight();
    int getDecel();
    bool getSuperJump();
    
    
    bool getWeaponEquip();
    int getInvincibleTime();
    int getInvurnableTime();
    int getCombatHitU();
    int getCombatHitD();
    int getCombatHitL();
    int getCombatHitR();
    float getCombatTime();
    float getCombatDelay();
    float getCombatCharge();
    float getCombatParryError();

    int getOffsetMidX();
    int getOffsetMidY();
    bool getUnfocusX();
    bool getUnfocusY();
    int getUnfocusOffsetX();
    int getUnfocusOffsetY();
    double getCameraScale();
    void setOffsetMidX(int x);
    void setOffsetMidY(int y);
    void setUnfocusX(bool focus);
    void setUnfocusY(bool focus);
    void setUnfocusOffsetX(int x);
    void setUnfocusOffsetY(int y);
    void setFocusFunction(FocusFunc focusFunc);

    int getAirCur();
    int getAirMax();
    int getHpCur();
    int getHpMax();

    bool getIsMove();
    bool getIsJump();
    bool getIsGDash();
    bool getIsADash();
    bool getIsCrawl();
    bool getIsHugWall();
    void setCanMove(bool can);
    void setCanJump(bool can);
    void setCanGDash(bool can);
    void setCanADash(bool can);
    void setCanCrawl(bool can);
    void setCanHugWall(bool can);

    // Method
    void playerMovement(Input *input);
    void playerCombat(Map *map, Input *input);

    void playerBlockCollision(std::vector<Block*> BlockVec);
    void playerEnemyCollision(std::vector<Enemy*> Enemy);
    void playerGetHit(int dmg);

    void playerSpriteIndex();
    void playerDrawSprite(SDL_Renderer *renderer);
    void playerUpdate(SDL_Renderer *renderer, Map *map, Input *input);

    void playerDeveloper(Input *input);
    void playerGrid(SDL_Renderer *renderer);

    void playerEnableAllMoveset();
};

#endif