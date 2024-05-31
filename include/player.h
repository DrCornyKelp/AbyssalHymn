#ifndef PLAYER_H
#define PLAYER_H

#include <hud.h>
#include <input.h>
#include <audio.h>
#include <particle_effect.h>

#define Player1D std::vector<Player*>
#define CameraBox1D std::vector<PlayerCameraBox>

class Map;
class Multiplayer;

struct PlayerCFG
{
    Player *player;

    // Deceleration
    float decel_mult = 2.5;
    float getDecelMult();

    // Ground Speed
    float vx_max = 6.5;
    float vx_ice_mult = 1.2;
    float vx_weapon_mult = .8;
    float vx_charge_mult = .8;
    void setVelXMax();

    // Ground Acceleration
    float ax = .1;
    float ax_ice = .06;
    float ax_weapon_mult = .8;
    float ax_charge_mult = .8;
    void setAccelX();

    // Air Acceleration
    float ay_tap = -.2;
    float ay_hold = -.1;
    float ay_weapon_mult = 1.2;
    float ay_charge_mult = 1.2;
    void setAccelY();

    // Jump
    float vy_jump_1 = 6.5;
    float vy_jump_2 = 5;
    float vy_super = 7.3;
    // Wall Jump
    float vx_wall = 8;
    float vy_wall = 4;

    // Ground Dash
    float gd_vx = 10;
    float gd_frame = 24;
    float gd_delay = 25;
    float gd_frame_crawl = 32;
    float gd_delay_crawl = 40;

    // Air Dash
    float ad_vx = 8;
    float ad_frame = 20;
};

struct PlayerMoveset
{
    bool move = 1;
    bool jump = 1;
    bool crawl = 1;
    bool g_dash = 1;
    bool a_dash = 1;
    bool hug_wall = 1;

    void enableAll();
    void disableAll();
};

struct PlayerCollide
{
    Player *player;

    bool lockU = 0;
    bool lockD = 0;
    bool lockL = 0;
    bool lockR = 0;
    void resetLock();

    bool predictU(Object2D *obj);
    bool predictD(Object2D *obj);
    bool predictL(Object2D *obj);
    bool predictR(Object2D *obj);

};

struct PlayerState
{
    bool on_ground = 0;
    bool on_ice = 0;
    bool in_water = 0;
    short hug_wall = 0;
    bool crawl_lock = 0;

    void resetState();

    // Special Condition
    bool jump_on_ice = 0;
};

struct PlayerMoving
{
    Player *player;
    // MOVING
    int decel = 0;
    float vx_max = 0;
    int vx_over_time = 0, // Time you spent over the speed cap
        vx_over_max = 100; // Max time before speed correction
    float vx_jump_saved = 0;
    // CRAWLING
    bool crawl = 0;
    float vx_crawl = .8;
    // Hitbox Offset
    int hit_offset_x = 0;
    int hit_offset_y = 0;
    float hitX();
    float hitY();
};

struct PlayerJumping
{
    Player *player;
    // Jumping
    int cur = 0,
        max = 2;
    float terminal = -10;
    // SUPER JUMPING
    int super = 0;
    int super_max = 80;
    // Coyote jump (forgiving jump)
    int coyote = 0;
    int coyote_max = 15;
    bool coyote_fail = 0;
    // Ceiling lock jump
    int ceiling_min = 10;
    int knockout = 0;

    void update();
};

struct PlayerAirDash
{
    Player *player;
    // 1 : lock right, -1 : lock left
    short lock = 0;
    int cur = 0;
    int max = 1;
    int frame = 0;
    
    void update();
};

struct PlayerGroundDash
{
    Player *player;
    bool super = 0;
    int frame = 0;
    int delay = 0;

    void update();
};

struct PlayerSprite
{
    Player *player;
    int index = 0;
    bool right = true;
    bool end_lock = false;
    int alpha = 255;

    SDL_Texture *CurrentTexture,
                *LeftTexture,
                *RightTexture,
                *LeftWeaponTexture,
                *RightWeaponTexture;

    SDL_Rect desRect, srcRect;

    void clearTexture();
    void setSpriteAlpha(int alp);

    void setAct(int idx, bool r);
    void setSprite(int m_index, int m_frame);
    void setEndLock(bool lock);
    void setActSprElock(int1D act, int1D spr, short lock = 0);

    void draw();
    void drawProp();
};

struct PlayerCameraBox
{
    ObjectBox box;
    ObjectBox cam;
};

struct PlayerCamera
{
    Player *player;

    /*
    Mid: Position Based Camera Offset
    - Based on the player's position
    Shift: The Camera Shift (include Effect and Ease)
    - Based on the player's movement
    Center_Off: The Average Position of the Players
    - Based on the number of players

    Offset: The True Camera Offset (include Mid, Shift and Center_Off)
    */

    ObjectXY mid;
    ObjectXY center_off; 
    ObjectXYf focus_trigger;
    ObjectXYb unfocus;
    ObjectXY unfocus_offset;
    ObjectXY offset;

    // Camera Shift Effect
    ObjectXYf shift;
    ObjectXYf ease;
    ObjectXYf effect;

    /*
    Most of the time camera will not snap to the player
    but ease to the player when encounter changes
    */

    // Goal Value
    ObjectBox focus_dir;
    ObjectBox focus_point;
    ObjectBox focus_border;
    bool outside_render = true;
    // Progress Value
    ObjectBox focus_true;
    int focus_speed = 4;
    bool focus_snap = 0;

    ObjectXYf getShift();
    ObjectXY getCenterOffset();
    ObjectXYf getFocusTrigger();

    void setCameraBorder(ObjectBox f_dir, ObjectBox f_val);
    void setCameraFocus(ObjectBox f_dir, ObjectBox f_val, short gr);
    void playerCameraFocus();

    void updateStatic();
    void updateDynamic();
};

struct PlayerCombat
{
    Player *player;
    // Invincibility (is when you are god)
    int invincible = 0;
    // Invulnerability (is when you get hurt)
    int invulnerable = 0;
    int invulnerable_max = 150;

    // Weapon handler
    bool weapon_equip = 0;
    int weapon_equip_frame = 0; // Only use for drawing
    int weapon_equip_delay = 0;
    int weapon_equip_delay_max = 200;

    int index = 0;
    float time = 0; 
    float combo_time = 0;
    int charge_time = 0;
    float delay = 0; 
    float parry_error = 0;
};

struct PlayerSFX
{
    Player *player;

    // AudioSFX hit = AudioSFX("assets/Audio/PlayerSFX/hit.mp3");
    AudioSFX jump = AudioSFX("assets/Audio/PlayerSFX/metalpipe.mp3");
    // AudioSFX dash = AudioSFX("assets/Audio/PlayerSFX/dash.mp3");
    // AudioSFX parry = AudioSFX("assets/Audio/PlayerSFX/parry.mp3");

    // Walking
    int walk_step = 0;
    int walk_sprite = 0;
    int walk_index = 0;
    AudioSFX walk0 = AudioSFX("assets/Audio/PlayerSFX/walk0.mp3");
    AudioSFX walk1 = AudioSFX("assets/Audio/PlayerSFX/walk1.mp3");
    AudioSFX walk2 = AudioSFX("assets/Audio/PlayerSFX/walk2.mp3");
    void updateWalkSFX();

    void updateSFX();
};

struct PlayerDeveloper
{
    Player *player;
    // Developer
    bool grid = 0;
    bool godmode = 0;

    void developer(Map *map);
};

class Player : public Object2D
{
public:
    // Elden ring
    int hp = 100;
    int hp_max = 100;
    int mp = 100;
    int mp_max = 100;

    // ================== META ===================
    bool MAIN;
    int INDEX;
    Input INPUT;
    Hud HUD = Hud(this);
    Multiplayer *MULTI;

    // ================== CONFIG =================
    PlayerCFG cfg = {this};

    // ================ STATE ====================
    PlayerState state;

    // ============ MOVEMENT/COMBAT ==============
    PlayerMoveset moveset;
    PlayerMoving move = {this};
    PlayerJumping jump = {this};
    PlayerAirDash a_dash = {this};
    PlayerGroundDash g_dash = {this};
    PlayerCollide collide = {this};
    PlayerCombat combat = {this};

    // ============== CAMERA/DRAW ================
    PlayerSprite psprite = {this}; // To avoid conflict with sprite
    PlayerCamera camera = {this};

    // ============== SOUND EFFECT ===============
    PlayerSFX sfx = {this};

    // ============== DEVELOPER ==================
    PlayerDeveloper dev = {this};

    // Constructor
    ~Player();
    Player(bool mc = 0);

    // Stop Player Current State
    void setStatic();

    // ========================= PLAYER LOGIC =========================
    void playerMovement(Map *map);
    void playerCombat(Map *map);
    void playerHitBox();
    void playerGetHit(Map *map, int dmg);
    void playerUpdate(Map *map);
};

#endif