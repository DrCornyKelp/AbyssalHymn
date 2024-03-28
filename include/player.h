#ifndef PLAYER_H
#define PLAYER_H

#include "input.h"
#include "block.h"
#include "enemy.h"
#include "particle_effect.h"

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
    float vel_x_max = 5;
    float vel_x_max_ground = 7;
    float vel_x_max_air = 6;
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
    float vel_terminal = -10;
    float accel_hold = -0.1;
    float accel_tap = -0.2;
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
    // invulnerable time (is when you get hurt)
    int invulnerable_time = 0;
    int invulnerable_time_max = 150;

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
    int combat_index = 0;
    float combat_parry_error = 0;

    // Combat Projectile
    bool jelly_keyhold = false;

    // ================= DRAWING ====================
    // Le Sprite itself (do not touch)
    SDL_Texture *playerCurrentTexture;
    SDL_Texture *PlayerLeft;
    SDL_Texture *PlayerRight;
    SDL_Texture *PlayerLeftWeapon;
    SDL_Texture *PlayerRightWeapon;

    SDL_Texture *PlayerSquid;
    
    // Action indexing and stuff idk
    int act_index = 0;
    bool act_right = true;

    // Sprite handler
    int sprite_alpha = 255;
    bool sprite_end_lock = false;
    int sprite_size = 64;

    // =========== EXTREMELY COMPLICATED CAMERA ============
    int offset_mid_x = 0;
    int offset_mid_y = 0;
    bool unfocus_x = 0;
    bool unfocus_y = 0;
    short unfocus_direction_y = 0; // 1 : up, -1: down
    int unfocus_offset_x = 0;
    int unfocus_offset_y = 0;
    FocusFunc focus_function;

    // Camera Effect
    float ease_x = 0;
    float ease_y = 0;
    float effect_x = 0;
    float effect_y = 0;

    // Vertical ahead
    int vertical_ahead_time = 0;
    int vertical_ahead_time_max = 150;
    float vertical_ahead = 0;
    float vertical_ahead_max = 192;

    double camera_scale = 1; // some good values 0.625 0.9375

    // ====== DEVELOPER VALUES ======
    SDL_Texture *hitbox;
    SDL_Texture *combatbox;

    bool godmode = false;
    bool godmode_hold;

    bool grid = false;
    bool grid_hold;

public:
    // Constructor
    Player(float X = 640, float Y = 400, int w = 128, int h = 128, int hw = 0, int hh = 0, int sim = 2, int sfm = 20, int si = 0, int sf = 0);
    void initPlayer(SDL_Renderer *renderer);

    // Movement
    int getDecel();
    bool getSuperJump();
    int getHitX();
    int getHitY();

    // Moveset
    bool getIsMove();
    bool getIsJump();
    bool getIsGDash();
    bool getIsADash();
    bool getIsCrawl();
    bool getIsHugWall();

    bool getCanHugWall();

    void setCanMove(bool can);
    void setCanJump(bool can);
    void setCanGDash(bool can);
    void setCanADash(bool can);
    void setCanCrawl(bool can);
    void setCanHugWall(bool can);

    void setHugWallLeft(bool hwl);
    void setHugWallRight(bool hwr);
    
    // Drawing
    int getActIndex();
    bool getActRight();
    void setActRight(bool ar);

    void setSprite(int m_index, int m_frame);
    void setSpriteAlpha(int alpha);
    void setAct(int index, bool right);
    void setEndLock(bool lock);

    // Combat
    bool getWeaponEquip();
    int getInvincibleTime();
    int getInvulnerableTime();
    float getCombatTime();
    float getCombatDelay();
    float getCombatCharge();
    float getCombatParryError();
    void setCombatDelay(float delay);
    void setInvincibleTime(int time);

    // Camera
    int getOffsetMidX();
    int getOffsetMidY();
    bool getUnfocusX();
    bool getUnfocusY();
    int getUnfocusOffsetX();
    int getUnfocusOffsetY();
    int getVerticalAhead();
    double getCameraScale();
    int getEaseX();
    int getEaseY();
    int getEffectX();
    int getEffectY();

    void setOffsetMidX(int x);
    void setOffsetMidY(int y);
    void setUnfocusX(bool focus);
    void setUnfocusY(bool focus);
    void setUnfocusOffsetX(int x);
    void setUnfocusOffsetY(int y);
    void setUnfocusDirectionY(short dir);
    void setFocusFunction(FocusFunc focusFunc);

    // Stat
    int getAirCur();
    int getAirMax();
    int getHpCur();
    int getHpMax();

    // Uncategorized
    void setOnGround(bool og);
    bool getOnGround();
    void setCrawlLock(bool cl);
    void setCeilingKnockout(int cko);
    void setBuffJumpTime(int bjt);

    // Method
    void playerMovement(Input *input);
    void playerCombat(Map *map, Input *input);

    void playerHitBox();
    void playerGetHit(int dmg);

    void playerDrawProperty();
    void playerCameraProperty(Input *input);
    void playerDrawSprite(SDL_Renderer *renderer);
    void playerUpdate(SDL_Renderer *renderer, Map *map, Input *input);

    void playerDeveloper(Input *input);
    void playerGrid(SDL_Renderer *renderer);

    void playerEnableAllMoveset();
};

#endif