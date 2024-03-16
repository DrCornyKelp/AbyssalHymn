#ifndef PLAYER_H
#define PLAYER_H

#include "block.h"
// #include "event_trigger.h"

#define FocusReturn(off, focus) return std::make_tuple(int(off), bool(focus))
#define FocusGet(result, index) std::get<index>(result)
#define FocusFunc std::tuple<int, bool>
typedef FocusFunc (*FocusXCondition)(int, int);
typedef FocusFunc (*FocusYCondition)(int, int);

class Player : public Object2D
{
private:
    // Elden ring
    int hp = 3;
    int hp_max = 3;
    int mp = 2;
    int mp_max = 2;
    int sta = 2;
    int sta_max = 2;

    // Ground movement
    float vel_x = 0;
    float vel_x_max = 5;
    float accel_x = 0.1;

    // Crawling
    bool crawl = false;
    float vel_crawl = .8;
    int hit_offset_x = 0;
    int hit_offset_y = 0;

    // Ground Dash
    bool g_dash = false;
    int g_dash_vel = 10;
    int g_dash_frame = 0;
    int g_dash_frame_max = 40;
    int g_dash_delay = 0;
    int g_dash_delay_max = 100;

    // Decelleration
    int decel_x = 0; // 0: none, -1: LEFT, 1: RIGHT

    // "Airborne" movement
    int air_cur = 3;
    int air_max = 3;

    // Jumping
    bool jump_hold = false;
    float vel_y = 0;
    float vel_terminal = 10;
    float accel_y = 0.1;
    float accel_hold = 0.1;
    float accel_tap = 0.2;
    // SUPER JUMPING
    int jump_super = 0;
    int jump_super_max = 80;

    // Air dash
    bool a_dash = false;
    int a_dash_frame = 0;
    int a_dash_frame_max = 20;

    // Action indexing and stuff idk
    int act_index = 0;
    bool act_right = true;

    // Sprite handler
    int sprite_alpha = 255;

    bool sprite_end_lock = false;

    // Drawing focus on player
    FocusXCondition fxcondition;
    bool focus_x = true;
    int offset_x;

    FocusYCondition fycondition;
    bool focus_y = false;
    int offset_y = 0;

    // Le Sprite itself (do not touch)
    Sprite *PlayerLeft;
    Sprite *PlayerRight;
    Sprite *hitbox;

    // Collision
    bool on_ground = false;
    bool hug_wall_resist = false;
    // !!! NOTE !!!
    bool hug_wall_left = false;
    bool hug_wall_right = false;

    // ====== EXPERIMENTATION VALUES ======
    bool display_hitbox = false;

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

    // Getter
    float getVelX();
    float getVelY();
    int getActIndex();
    bool getActRight();
    int getDecel();
    
    int getHitX();
    int getHitY();

    // Thing that will be drawn in stat
    int getAirCur();
    int getAirMax();
    int getHpCur();
    int getHpMax();

    bool getFocusX();
    bool getFocusY();
    int getOffsetX();
    int getOffsetY();

    // Method
    void playerInput();
    void playerMovement();
    void playerTileCollision(std::vector<Block> BlockVec);
    void playerNpcCollision();
    // void playerEventTrigger(EventTrigger *event[]);

    void playerAction();
    void playerSprite(SDL_Renderer *renderer);
    void playerUpdate(SDL_Renderer *renderer, std::vector<Block> Blockvec);
};

#endif