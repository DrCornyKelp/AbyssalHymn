#ifndef PLAYER_H
#define PLAYER_H

#include <hud.h>
#include <input.h>
#include <particle_effect.h>

#define Player1D std::vector<Player*>
#define CameraBox1D std::vector<PlayerCameraBox>

class Map;
class Multiplayer;

struct PlayerCameraBox
{
    ObjectBox box;
    ObjectBox cam;
};

struct PlayerMoveset
{
    bool move = 1;
    bool jump = 1;
    bool crawl = 1;
    bool g_dash = 1;
    bool a_dash = 1;
    bool hug_wall = 1;
};

struct PlayerState
{
    bool on_ground = 0;
    bool on_ice = 0;
    bool in_water = 0;
    short hug_wall = 0;
    bool crawl_lock = 0;

    void resetState();
};

struct PlayerCondition
{
    bool jump_on_ice = 0;
};

struct PlayerMoving
{
    Player *player;
    // MOVING
    int decel = 0;
    float vel_max = 5;
    int vel_over_time = 0, // Time you spent over the speed cap
        vel_over_max = 100; // Max time before speed corretion
    float vel_jump_saved = 0;
    // CRAWLING
    bool crawl = 0;
    float vel_crawl = .8;
    int hit_offset_x = 0;
    int hit_offset_y = 0;

    int hitX();
    int hitY();
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
    int knockout_delay = 50;
};

struct PlayerAirDash
{
    Player *player;
    // 1 : lock right, -1 : lock left
    short lock = 0;
    int cur = 0;
    int max = 1;
    int frame = 0;
};

struct PlayerGroundDash
{
    Player *player;
    bool super = 0;
    int frame = 0;
    int delay = 0;
};

struct PlayerCamera
{
    Player *player;
    int mid_x = 0;
    int mid_y = 0;
    bool unfocus_x = 0;
    bool unfocus_y = 0;
    int unfocus_offset_x = 0;
    int unfocus_offset_y = 0;
    int shift_x = 0;
    int shift_y = 0;

    int offset_x = 0;
    int offset_y = 0;

    ObjectXY center_off; // For >1 players

    // Goal Value
    ObjectBox focus_dir;
    ObjectBox focus_point;
    ObjectBox focus_border;
    bool outside_render = true;
    // Progress Value
    ObjectBox focus_true;
    int focus_speed = 4;
    bool focus_snap = 0;

    // Camera Effect
    float ease_x = 0;
    float ease_y = 0;
    float effect_x = 0;
    float effect_y = 0;

    ObjectXY getCenterOffset();
    int getShiftX();
    int getShiftY();
    int getFocusTriggerX();
    int getFocusTriggerY();

    void resetCamera();
    void setCameraBorder(ObjectBox f_dir, ObjectBox f_val);
    void setCameraFocus(ObjectBox f_dir, ObjectBox f_val, short gr);
    void playerCameraFocus();
    void playerCameraProperty(Input *input);
};

struct PlayerDrawProp
{
    Player *player;
    int index = 0;
    bool right = true;
    int alpha = 255;
    bool end_lock = false;

    SDL_Texture *CurrentTexture;
    SDL_Texture *LeftTexture;
    SDL_Texture *RightTexture;
    SDL_Texture *LeftWeaponTexture;
    SDL_Texture *RightWeaponTexture;

    SDL_Rect des_rect;
    SDL_Rect src_rect;

    void clearTexture();
    void setSpriteAlpha(int alp);

    void setAct(int idx, bool r);
    void setSprite(int m_index, int m_frame);
    void setEndLock(bool lock);
    void setActSprElock(int1D act, int1D spr, short lock = 0);

    void draw();
    void drawProperty(Map *map);
};

struct PlayerSFX
{
    sf::SoundBuffer
        jumpB, moveB;
    sf::Sound
        jumpS, moveS;
};

struct PlayerCombat
{
    Player *player;
    // Invincibility (is when you are god)
    int invincible = 0;
    // invulnerable time (is when you get hurt)
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

class Player : public Object2D
{
private:
    // Elden ring
    int hp = 100;
    int hp_max = 100;
    int mp = 100;
    int mp_max = 100;

    // ====== DEVELOPER VALUES ======

    bool grid = 0;
    int grid_save_x = 0;
    int grid_save_y = 0;

    bool godmode = false;

public:
    // ================== META ===================
    bool MAIN;
    int INDEX;
    Input INPUT;
    Hud HUD = Hud(this);
    Multiplayer *MULTI;

    // ================== STATE ==================
    PlayerState state;
    PlayerCondition condition;

    // ============ MOVEMENT/COMBAT ==============
    PlayerMoveset moveset;
    PlayerMoving move = {this};
    PlayerJumping jump = {this};
    PlayerAirDash a_dash = {this};
    PlayerGroundDash g_dash = {this};
    PlayerCombat combat = {this};

    // ============== CAMERA/DRAW ================
    PlayerDrawProp draw_prop = {this};
    PlayerCamera camera = {this};

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
    void playerEnableAllMoveset();

    // Developer
    bool getGodmode(); // Only needed in collision checking
    void playerDeveloper(Map *map);
};

#endif