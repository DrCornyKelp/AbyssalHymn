#ifndef PLAYER_H
#define PLAYER_H

#include "block.h"
#include "enemy.h"

#define FocusReturn(off, focus) return std::make_tuple(int(off), bool(focus))
#define FocusGet(result, index) std::get<index>(result)
#define FocusFunc std::tuple<int, bool>
typedef FocusFunc (*FocusXCondition)(int, int);
typedef FocusFunc (*FocusYCondition)(int, int);

class Map;
class Player : public Object2D
{
private:
    // Elden ring
    int hp = 3;
    int hp_max = 3;
    int mp = 2;
    int mp_max = 2;

    // Moveset availability
    bool can_move = true;
    bool can_jump = false;
    bool can_crawl = false;
    bool can_g_dash = false;
    bool can_a_dash = false;
    bool can_hug_wall = false;

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
    int decel_x = 0; // 0: none, -1: LEFT, 1: RIGHT

    // "Airborne" movement
    int air_cur = 0;
    int air_max = 3;

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
    int a_dash_frame = 0;
    int a_dash_frame_max = 0;
    int a_dash_frame_normal = 30;
    int a_dash_frame_weapon = 20;
    int a_dash_delay = 0;
    int a_dash_delay_max = 0;
    int a_dash_delay_normal = 40;
    int a_dash_delay_weapon = 100;

    // Ground Dash
    bool g_dash = false;
    int g_dash_vel = 10;
    int g_dash_frame = 0;
    int g_dash_frame_max = 0;
    int g_dash_frame_normal = 40;
    int g_dash_frame_weapon = 30;
    int g_dash_delay = 0;
    int g_dash_delay_max = 0;
    int g_dash_delay_normal = 40;
    int g_dash_delay_weapon = 100;

    // ================== Combat ===================

    // Invincibility
    int invincible_time = 0;
    int invincible_time_max = 100;

    // Weapon handler
    bool weapon_equip = true;
    bool weapon_equip_keyhold = false;
    int weapon_equip_delay = 0;
    int weapon_equip_delay_max = 30;

    // Time the atk exist
    int combat_time = 0; 
    // Time you perform follow up
    int combat_combo_time = 0;
    // The ...well, delay lmao
    int combat_delay = 0; 
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

    // ================= DRAWING ====================
    // Le Sprite itself (do not touch)
    SDL_Texture *playerCurrentTexture;
    Sprite *PlayerLeft;
    Sprite *PlayerRight;
    Sprite *PlayerLeftWeapon;
    Sprite *PlayerRightWeapon;
    Sprite *PlayerParryEffect;
    
    // Action indexing and stuff idk
    int act_index = 0;
    bool act_right = true;

    // Sprite handler
    int sprite_alpha = 255;
    bool sprite_end_lock = false;
    int sprite_size = 64;

    // Drawing focus on player
    FocusXCondition fxcondition;
    bool focus_x = true;
    int offset_x;
    FocusYCondition fycondition;
    bool focus_y = false;
    int offset_y = 0;

    // ====== DEVELOPER VALUES ======
    Sprite *hitbox;
    Sprite *combatbox;

    bool godmode = false;
    bool godmode_hold;

    bool grid = false;
    bool grid_hold;

    // FUNNNNNNNNNNNNNNNN

public:
    // Constructor
    Player(float X = 640, float Y = 400, int w = 128, int h = 128, int hw = 0, int hh = 0, int sim = 2, int sfm = 20, int si = 0, int sf = 0);
    void initPlayer(SDL_Renderer *renderer);

    // Setter
    void setVelX(float X);
    void setVelY(float Y);
    
    void setSprite(int m_index, int m_frame);
    void setSpriteAlpha(int alpha);
    void setAct(int index, bool right);
    void setEndLock(bool lock);

    void setFocusXCondition(FocusXCondition fcond);
    void setFocusYCondition(FocusYCondition fcond);
    void setFocus();

    void setCanMove(bool can);
    void setCanJump(bool can);
    void setCanGDash(bool can);
    void setCanADash(bool can);
    void setCanCrawl(bool can);
    void setCanHugWall(bool can);

    void setCombatDelay(int delay);

    // Getter
    float getVelX();
    float getVelY();
    int getActIndex();
    bool getActRight();
    int getDecel();
    bool getSuperJump();
    
    int getHitX();
    int getHitY();
    
    int getInvincibleTime();
    bool getWeaponEquip();
    int getCombatHitU();
    int getCombatHitD();
    int getCombatHitL();
    int getCombatHitR();
    int getCombatTime();
    int getCombatDelay();
    Sprite *getPlayerParrySprite();

    int getAirCur();
    int getAirMax();
    int getHpCur();
    int getHpMax();

    bool getFocusX();
    bool getFocusY();
    int getOffsetX();
    int getOffsetY();

    bool getIsMove();
    bool getIsJump();
    bool getIsGDash();
    bool getIsADash();
    bool getIsCrawl();
    bool getIsHugWall();

    // Method
    void playerInput();
    void playerMovement();
    void playerCombat();

    void playerBlockCollision(std::vector<Block*> BlockVec);
    void playerEnemyCollision(std::vector<Enemy*> Enemy);
    void playerGetHit(int dmg);

    void playerSpriteIndex();
    void playerDrawSprite(SDL_Renderer *renderer);
    void playerUpdate(SDL_Renderer *renderer, Map *map);

    void playerDeveloper();
    void playerGrid(SDL_Renderer *renderer);

    void playerEnableAllMoveset();
};

#endif