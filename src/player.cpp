#include <player.h>
#include <map.h>

// Constructor
Player::Player(float X, float Y, int w, int h, int hw, int hh, int sim, int sfm, int si, int sf) : Object2D(X, Y, w, h, hw, hh, sim, sfm, si, sf) {}

// Fuck her 2nite
void Player::initPlayer(SDL_Renderer *renderer)
{
    // Nakuru normal mvoement
    PlayerRight = new Sprite(32, 32, 1, "res/NakuSheet/NakuRight.png");
    PlayerRight->setTexture(Sprite::loadTexture(renderer, PlayerRight->getSpritePath()));

    PlayerLeft = new Sprite(32, 32, 1, "res/NakuSheet/NakuLeft.png");
    PlayerLeft->setTexture(Sprite::loadTexture(renderer, PlayerLeft->getSpritePath()));

    // Nakuru holding weapon
    PlayerRightWeapon = new Sprite(64, 64, 1, "res/NakuSheet/NakuRightWeapon.png");
    PlayerRightWeapon->setTexture(Sprite::loadTexture(renderer, PlayerRightWeapon->getSpritePath()));

    PlayerLeftWeapon = new Sprite(64, 64, 1, "res/NakuSheet/NakuLeftWeapon.png");
    PlayerLeftWeapon->setTexture(Sprite::loadTexture(renderer, PlayerLeftWeapon->getSpritePath()));

    // Nakuru Squid Game
    PlayerSquid = new Sprite(64, 64, 1, "res/NakuSheet/NakuSquid.png");
    PlayerSquid->setTexture(Sprite::loadTexture(renderer, PlayerSquid->getSpritePath()));

    // EXPERIMENTATION
    hitbox = new Sprite(100, 100, 1, "res/HitboxMyass.png");
    hitbox->setTexture(Sprite::loadTexture(renderer, hitbox->getSpritePath()));

    combatbox = new Sprite(100, 100, 1, "res/CombatMyass.png");
    combatbox->setTexture(Sprite::loadTexture(renderer, combatbox->getSpritePath()));
};

// Setter
void Player::setAct(int index, bool right)
{
    if (act_index != index || act_right != right)
    {
        act_index = index;
        act_right = right;
    }
}

void Player::setSprite(int m_index, int m_frame)
{ setSprFrameMax(m_frame); setSprIndexMax(m_index); }

void Player::setSpriteAlpha(int alpha)
{
    if (sprite_alpha != alpha)
    {
        sprite_alpha = alpha;
        SDL_SetTextureAlphaMod(playerCurrentTexture, alpha);
    }
}

void Player::setEndLock(bool lock)
{
    if (lock && !sprite_end_lock)
    {
        setSprFrame(0);
        setSprIndex(0);
    }
    sprite_end_lock = lock;
}

// Moveset
bool Player::getIsMove() { return vel_x; }
bool Player::getIsJump() { return vel_y; }
bool Player::getIsGDash() { return g_dash; }
bool Player::getIsADash() { return a_dash; }
bool Player::getIsCrawl() { return crawl; }
bool Player::getIsHugWall() { return hug_wall_left || hug_wall_right; }

void Player::setCanMove(bool can) { can_move = can; }
void Player::setCanJump(bool can) { can_jump = can; }
void Player::setCanCrawl(bool can) { can_crawl = can; }
void Player::setCanGDash(bool can) { can_g_dash = can; }
void Player::setCanADash(bool can) { can_a_dash = can; }
void Player::setCanHugWall(bool can) { can_hug_wall = can; }

// Movement
float Player::getVelX() { return vel_x; }
float Player::getVelY() { return vel_y; }
void Player::setVelX(float X) { vel_x = X; }
void Player::setVelY(float Y) { vel_y = Y; }
int Player::getAirCur() { return air_cur; }
int Player::getAirMax() { return air_max; }
int Player::getDecel() { return decel_x; }
bool Player::getSuperJump() { return jump_super >= jump_super_max; }

// Action speak louder than word
// "Going to the mall is louder than... green?"
int Player::getActIndex() { return act_index; }
bool Player::getActRight() { return act_right; }

// Combat / Hitbox
int Player::getHpCur() { return hp; }
int Player::getHpMax() { return hp_max; }

int Player::getHitX() { return getX() + hit_offset_x; }
int Player::getHitY() { return getY() + hit_offset_y; }

bool Player::getWeaponEquip() { return weapon_equip; }
int Player::getInvincibleTime() { return invincible_time; }
int Player::getInvulnerableTime() { return invulnerable_time; }

int Player::getCombatHitU() { return combat_hit_up; }
int Player::getCombatHitD() { return combat_hit_down; }
int Player::getCombatHitL() { return combat_hit_left; }
int Player::getCombatHitR() { return combat_hit_right; }
float Player::getCombatTime() { return combat_time; }
float Player::getCombatDelay() { return combat_delay; }
float Player::getCombatCharge() { return combat_charge_time; }
float Player::getCombatParryError() { return combat_parry_error; }

void Player::setCombatDelay(float delay) { combat_delay = delay; }
void Player::setInvincibleTime(int time) { invincible_time = time; }

// Camera
int Player::getOffsetMidX() { return offset_mid_x; }
int Player::getOffsetMidY() { return offset_mid_y; }
bool Player::getUnfocusX() { return unfocus_x; }
bool Player::getUnfocusY() { return unfocus_y; }
int Player::getUnfocusOffsetX() { return unfocus_offset_x; }
int Player::getUnfocusOffsetY() { return unfocus_offset_y; }
int Player::getVerticalAhead() { return vertical_ahead; }
double Player::getCameraScale() { return camera_scale; }

int Player::getEaseX() { return ease_x; }
int Player::getEaseY() { return ease_y; }
int Player::getEffectX() { return effect_x; }
int Player::getEffectY() { return effect_y; }

void Player::setOffsetMidX(int x) { offset_mid_x = x; }
void Player::setOffsetMidY(int y) { offset_mid_y = y; }
void Player::setUnfocusX(bool focus) { unfocus_x = focus; }
void Player::setUnfocusY(bool focus) { unfocus_y = focus; }
void Player::setUnfocusOffsetX(int x) { unfocus_offset_x = x; }
void Player::setUnfocusOffsetY(int y) { unfocus_offset_y = y; }
void Player::setUnfocusDirectionY(short dir) { unfocus_direction_y = dir; }
void Player::setFocusFunction(FocusFunc focusFunc) { focus_function = focusFunc; }

// Other Method

void Player::playerDrawSprite(SDL_Renderer *renderer)
{
    Camera::objectSetSprite(this, sprite_end_lock);

    int drawX = Game::WIDTH / 2 + (offset_mid_x - sprite_size*2) * camera_scale; 
    int drawY = Game::HEIGHT / 2 - (offset_mid_y + sprite_size*2) * camera_scale;
    // The -1 is just to make the drawing look abit better, dont worry

    SDL_Rect desRect = {int(drawX) + Camera::playerShiftX(this),
                        int(drawY) + Camera::playerShiftY(this),
                        int(sprite_size * 4 * camera_scale), 
                        int(sprite_size * 4 * camera_scale)};
    SDL_Rect srcRect = {getSprIndex() * sprite_size, act_index * sprite_size, sprite_size, sprite_size};

    if (!invulnerable_time)
        SDL_SetTextureAlphaMod(playerCurrentTexture, 255);
    SDL_RenderCopy(renderer, playerCurrentTexture, &srcRect, &desRect);
}

void Player::playerDrawProperty()
{   
    // ======================== SRPITES ===========================
    // Set index and stuff
    act_right = vel_x > .2 ? 1 : vel_x < -.2 ? 0 : act_right;

    // Ow< ouch
    if (invulnerable_time > invulnerable_time_max * .8)
    {
        setAct(8, act_right);
        setSprite(1, 0);
        effect_x = effect_x > 0 ? 20 : -20;

        return;
    }

    // Movement
    if (!combat_index)
    {
        if (abs(vel_x) <= .2)
        {
            // Idling
            setAct(0, act_right);
            setSprite(2, 64);
        }
        else
        {
            // Moving
            setAct(1, act_right);
            setSprite(8, 30 - abs(vel_x) * 4);
        }

        // Decelerating
        if (decel_x != 0)
        {
            setAct(2, decel_x > 0);
            setSprite(2, 2);
        }

        // Jumping
        if (vel_y > .2 && !on_ground)
        {
            setAct(3, act_right);
            setSprite(4, 16);
        }
        if (vel_y < .2 && !on_ground)
        {
            setAct(3, act_right);
            setSprite(8, 4);
        }

        // Ground Dashing
        if (g_dash)
        {
            setEndLock(true);
            setAct(4, act_right);
            setSprite(8, 3);
        }
        // Air Dashing
        if (a_dash)
        {
            setEndLock(true);
            setAct(5, act_right);
            setSprite(4, 10);
        }

        // Crawl
        if (crawl && !(g_dash && crawl_lock))
        {
            setAct(6, act_right);
            setSprite((abs(vel_x) > 0 ? 4 : 1), 8);
        }

        // Wall Sliding
        if (hug_wall_left || hug_wall_right)
        {
            setAct(7, hug_wall_right);
            setSprite(4, 8);
        }
    }
    else
    {
        // ============= COMBAT SPRITE =============

        // Figthing
        if (combat_index == 1 && combat_time)
        {
            setAct(10, act_right);
            setSprite(8, buff_combat_speed < 1.2 ? 2 : 1);
            setEndLock(true);
        }

        if (combat_index == 2 && combat_time)
        {
            setAct(11, act_right);
            setSprite(8, buff_combat_speed < 1.2 ? 2 : 1);
            setEndLock(true);
        }

        if (combat_index == 3)
        {
            if (combat_keyhold)
            {
                setAct(12, act_right);
                setSprite(vel_x ? 4 : 1, 30 - abs(vel_x) * 4);
            }
            else
            {
                setAct(13, act_right);
                setSprite(4, buff_combat_speed < 1.2 ? 2 : 1);
                setEndLock(true);
            }
        }

        if (combat_index == 4 && combat_time)
        {
            setAct(14, act_right);
            setSprite(8, 2);
            setEndLock(true);
        }

        if (combat_index == 5 && combat_time)
        {
            setAct(15, act_right);
            setSprite(8, 1);
            setEndLock(true);
        }
    }

    // Weapon draw
    if (weapon_equip_frame)
    {
        if (weapon_equip)
        {
            setAct(9, act_right);
            setSprite(8, 3);
        }
    }

    if (!a_dash && !g_dash && !weapon_equip_delay && !combat_index)
        setEndLock(false);

    // ============= SET SPRITE ==============

    playerCurrentTexture = act_right ? 
        (weapon_equip ? PlayerRightWeapon->getTexture() :
                        PlayerRight->getTexture()) :
        (weapon_equip ? PlayerLeftWeapon->getTexture() :
                        PlayerLeft->getTexture());

    sprite_size = weapon_equip ? 64 : 32;
}

void Player::playerCameraProperty(Input *input)
{
    // ======================== CAMERA ============================

    // Camera focus
    focus_function(this);

    // Damping / Easing effect
    if (act_right &&
        ease_x > -64 * (weapon_equip ? 1 : 1.5))
        ease_x -= abs(vel_x / 5);
    if (!act_right &&
        ease_x < 64 * (weapon_equip ? 1 : 1.5))
        ease_x += abs(vel_x / 5);
    if (!vel_x && ease_x) ease_x -= ease_x / 40;

    // Look vertical up and down
    float vt_max = vertical_ahead_max;
    if (on_ground && !vel_x && !unfocus_y &&
        vertical_ahead_time > vertical_ahead_time_max)
    {
        if (input->getButton(0) && vertical_ahead < vt_max &&
            !(unfocus_direction_y == 1 && getY() > unfocus_offset_y - vt_max))
            vertical_ahead += (vt_max - abs(vertical_ahead)) / 30;
        if (input->getButton(1) && vertical_ahead > -vt_max &&
            !(unfocus_direction_y == -1 && getY() < unfocus_offset_y + vt_max))
            vertical_ahead -= (vt_max - abs(vertical_ahead)) / 30;

        vertical_ahead = vertical_ahead > vt_max ? vt_max : vertical_ahead;
        vertical_ahead = vertical_ahead < -vt_max ? -vt_max : vertical_ahead;
    }

    if (on_ground && !vel_x && !unfocus_y &&
        (input->getButton(0) || input->getButton(1)))
        vertical_ahead_time ++;
    else vertical_ahead_time = 0;

    if ((!input->getButton(0) && vertical_ahead > 0) ||
        (!input->getButton(1) && vertical_ahead < 0))
        vertical_ahead -= vertical_ahead / 40;

    if (a_dash || g_dash)
    {
        effect_x += vel_x > 0 ? -2 : 2;
        effect_x = effect_x > 64 ? 64 : effect_x;
        effect_x = effect_x <-64 ?-64 : effect_x;
    }
    else if (effect_x) effect_x -= effect_x / 40;
}

void Player::playerMovement(Input *input)
{
// ======================== MOVEMENT INPUT ==============================
    bool hug_wall = hug_wall_left || hug_wall_right;

    // Moving L/R
    if (can_move && !g_dash && !a_dash && !crawl)
    {
        if (input->getButton(2) && !hug_wall_right)
        {
            if (hug_wall_left)
            {
                hug_wall_left = false;
                setX(getX() - 4);
            }

            if (vel_x > 1)
            {
                decel_x = 1;
                vel_x -= accel_x * 2.5;
            }
            else
            {
                decel_x = 0;
                vel_x -= accel_x;
            }
        }

        if (input->getButton(3) && !hug_wall_left)
        {
            if (hug_wall_right)
            {
                hug_wall_right = false;
                setX(getX() + 4);
            }

            if (vel_x < -1)
            {
                decel_x = -1;
                vel_x += accel_x * 2.5;
            }
            else
            {
                decel_x = 0;
                vel_x += accel_x;
            }
        }
    }

    // Crawling
    crawl = can_crawl && input->getButton(1) && on_ground && !g_dash && !decel_x && !g_dash_delay && abs(vel_x) < vel_x_max / 2;
    crawl = crawl_lock || crawl;

    if (crawl && input->getButton(2) && !g_dash)
        vel_x = -vel_crawl;
    if (crawl && input->getButton(3) && !g_dash)
        vel_x = vel_crawl;

    // Deceleration
    if ((!input->getButton(2) && decel_x == 1) ||
        (!input->getButton(3) && decel_x == -1))
        decel_x = 0;

    if (!input->getButton(2) && !input->getButton(3) && !g_dash && !a_dash)
    {
        if (abs(vel_x) >= accel_x)
        {
            int direction = (vel_x < 0 ? 1 : -1);
            vel_x += accel_x * direction;
        }
        else
            vel_x = 0;
    }

    // Ground dash (more like sliding but whatever)
    if (can_g_dash && input->getButton(5) && !g_dash_delay && !combat_index && on_ground && !g_dash && !crawl_lock && !a_dash)
    {
        g_dash = true;
        g_dash_delay = g_dash_delay_max * (crawl ? 1.5 : 1);
    }

    // Air dash
    if (can_a_dash && input->getButton(5) && !a_dash_delay && !combat_index && !on_ground && !hug_wall && !crawl && !g_dash && vel_x != 0 && air_cur > 0 && !jump_keyhold)
    {
        a_dash = true;
        air_cur--;
        a_dash_delay = a_dash_delay_max;
    }

    // Jump held key
    if (can_jump && input->getButton(4) && !jump_keyhold && (air_cur > 0 || hug_wall) &&
        !g_dash && !a_dash && !decel_x && !crawl_lock && !ceiling_knockout)
    {
        setY(getY() + 10);
        on_ground = false;

        vel_y = 1 + 40 / (air_max - air_cur + 8);
        if (jump_super == jump_super_max)
            vel_y = 7.3;

        // Wall jump
        if (!hug_wall)
            air_cur--;
        if (hug_wall_left)
        {
            vel_x = -10;
            vel_y = 4;
            setX(getX() - getHitWidth() / 2);
        }
        if (hug_wall_right)
        {
            vel_x = 10;
            vel_y = 4;
            setX(getX() + getHitWidth() / 2);
        }

        hug_wall_left = false;
        hug_wall_right = false;

        jump_keyhold = true;
    }
    // Jump release key
    if (!input->getButton(4))
    {
        jump_keyhold = false;
    }

// ======================== MOVEMENT LOGIC ==============================

    // Buff Movement
    if (buff_move_time)
        buff_move_time--;
    else
        buff_move = 1;
    
    if (buff_jump_time)
        buff_jump_time--;
    else
        buff_jump = 1;

    // Velcovity
    vel_x_max = on_ground ? vel_x_max_ground : vel_x_max_air;
    vel_x_max *=(weapon_equip ? .8 : 1) *
                (combat_charge_time ? .8 : 1) *
                buff_move;
    // Acceleration x
    accel_x = on_ice ? accel_x_ice : accel_x_ground;
    accel_x *=  (weapon_equip ? .8 : 1) *
                (combat_charge_time ? .8 : 1) *
                buff_move;
    // Acceleration y
    accel_y = jump_keyhold ? accel_hold : accel_tap;
    accel_y *=  (weapon_equip ? 1.2 : 1) *
                (combat_charge_time ? 1.2 : 1) *
                buff_jump;
    // G_dash
    g_dash_vel = weapon_equip ? g_dash_vel_weapon : g_dash_vel_normal;
    g_dash_vel *= buff_move;
    g_dash_frame_max = weapon_equip ? g_dash_frame_weapon : g_dash_frame_normal;
    g_dash_delay_max = weapon_equip ? g_dash_delay_weapon : g_dash_delay_normal;
    // A_dash
    a_dash_frame_max = weapon_equip ? a_dash_frame_weapon : a_dash_frame_normal;
    a_dash_delay_max = weapon_equip ? a_dash_delay_weapon : a_dash_delay_normal;

    // Cap X velocity
    if (!g_dash && !a_dash)
    {
        if (vel_x < -vel_x_max)
            vel_x = -vel_x_max;
        if (vel_x > vel_x_max)
            vel_x = vel_x_max;
    }
    
    setX(getX() + vel_x);

    // Vertigo is a bad map
    if (vel_y < 0)
        accel_y = accel_tap;

    if (on_ground)
        vel_y = 0;
    else if (hug_wall_left || hug_wall_right)
        vel_y = -1;
    else
        vel_y -= accel_y;

    // Terminal Velocity
    if (vel_y <= -vel_terminal)
        vel_y = -vel_terminal;

    // SUPER JUMP
    if (crawl && !crawl_lock && vel_x == 0)
        jump_super += jump_super < jump_super_max;
    else
        jump_super = 0;

    // Ground dash
    if (g_dash)
    {
        g_dash_frame++;
        vel_x = g_dash_vel * (act_right ? 1 : -1) * (crawl ? 1.4 : 1);
        if (g_dash_frame >= g_dash_frame_max)
        {
            g_dash_frame = 0;
            g_dash = false;
        }
    }

    if (g_dash_delay > 0)
        g_dash_delay--;

    // a_Dashing
    if (a_dash)
    {
        a_dash_frame++;
        
        // :3
        vel_x = (3 + 90 / (air_max - air_cur + 6)) * (vel_x > 0 ? 1 : -1);
        vel_y = 0;

        if (a_dash_frame >= a_dash_frame_max)
        {
            a_dash_frame = 0;
            a_dash = false;
        }
    }

    if (a_dash_delay > 0)
        a_dash_delay--;

    // Ceiling knock out
    if (ceiling_knockout > 0)
        ceiling_knockout--;

    // On ground
    if (!on_ground && air_cur == air_max)
        air_cur = air_max - 1;
    if (on_ground)
        air_cur = air_max;

    setY(getY() + vel_y);
}

void Player::playerCombat(Map *map, Input *input)
{
// ======================== COMBAT INPUT ==============================

    bool hug_wall = hug_wall_left || hug_wall_right;

    // Weapon equipment
    if (input->getButton(7) && !weapon_equip_delay && on_ground)
    {
        setSprIndex(0);
        weapon_equip_frame = 24;
        weapon_equip_delay = weapon_equip_delay_max;
        weapon_equip = weapon_equip ? false : true;
    };
    // Weapon draw ("draw" weapon, not "draw" painting) delay
    if (weapon_equip_delay > 0)
        weapon_equip_delay -= buff_combat_speed;
    if (weapon_equip_frame) 
        weapon_equip_frame --;

    // Attack pattern (really fucking sophisicated)
    if (input->getButton(6))
    {
        combat_keytime++;
        combat_keyhold = !combat_keytap && combat_keytime > 20;
    }
    else
    {
        combat_keytap = combat_keytime <= 20 && combat_keytime > 0;
        combat_keyhold = false;
        combat_keytime = 0;
    }

    // Special Jelly Projectile
    if (weapon_equip && input->getButton(8) && !jelly_keyhold)
    {
        jelly_keyhold = true;
        map->ProjectileVec.push_back(new Projectile(
            PlayerSquid->getTexture(), getX(), getY(), 16, 16, 32, 32, act_right * 2 - 1, vel_y + 10, 0, -.2, 10, 1000, -1, 1, 1, 0, 4, 10
        ));
    }
    if (!input->getButton(8) && jelly_keyhold)
        jelly_keyhold = false;

// ======================== COMBAT LOGIC ==============================

    // Buff Combat
    if (buff_combat_speed_time)
        buff_combat_speed_time--;
    else
        buff_combat_speed = 1;
    
    if (buff_combat_damage_time)
        buff_combat_damage_time--;
    else
        buff_combat_damage = 1;

    // Invincibility frame
    if (invincible_time)
        invincible_time--;

    if (invulnerable_time) {
        invulnerable_time--;

        if (invulnerable_time > invulnerable_time_max * .8)
        {
            // When got hit reset all movement and stuff
            vel_x = 0;
            vel_y = 0;

            a_dash = 0;
            g_dash = 0;

            combat_charge_time = 0;
            combat_combo_time = 0;
            combat_time = 0;
            combat_index = 0;
        }
        SDL_SetTextureAlphaMod(playerCurrentTexture, (invulnerable_time % 15 > 0) ? 200 : 160);
    }

    if (combat_time > 0)
        combat_time -= buff_combat_speed;
    else
        combat_time = 0;
    
    if (combat_combo_time > 0)
        combat_combo_time--;
    else
    {
        combat_combo_time = 0;
        combat_index = 0;
    }

    if (combat_delay > 0)
        combat_delay -= buff_combat_speed;
    else
        combat_delay = 0;

    if (!weapon_equip) return;

    // =================== Combat hitbox handler ===================
    if (!combat_time && !a_dash && !g_dash)
    {
        combat_hit_up = 0;
        combat_hit_down = 0;
        combat_hit_right = 0;
        combat_hit_left = 0;
        combat_damage = 0;
        combat_parry_error = 10;
    }

    if (a_dash)
    {
        combat_hit_up = 30;
        combat_hit_down = 30;
        combat_damage = 10;
        if (act_right)
            combat_hit_right = 80;
        else
            combat_hit_left = 80;
    }

    if (g_dash)
    {
        combat_hit_up = 20;
        combat_hit_down = 20;
        if (act_right) combat_hit_right = 80;
        else combat_hit_left = 80;

        combat_damage = crawl ? 20 : 12;
    }

    if (combat_index == 1)
    {
        combat_hit_up = 40;
        combat_hit_down = 40;
        combat_hit_right = act_right ? 100 : 0;
        combat_hit_left = act_right ? 0 : 100;
        combat_damage = 10;
        combat_parry_error = 3;
    }

    if (combat_index == 2)
    {
        combat_hit_up = 15;
        combat_hit_down = 15;
        combat_hit_right = act_right ? 120 : 0;
        combat_hit_left = act_right ? 0 : 120;
        combat_damage = 20;
        combat_parry_error = 1;
    }

    if (combat_index == 3)
    {
        combat_hit_up = 80;
        combat_hit_down = 60;
        combat_hit_right = act_right ? 130 : 0;
        combat_hit_left = act_right ? 0 : 130;
        combat_damage = 30;
        combat_parry_error = 0;
    }

    if (combat_index == 4)
    {
        combat_hit_up = 76;
        combat_hit_down = 0;
        combat_hit_right = 64;
        combat_hit_left = 64;
        combat_damage = 15;
        combat_parry_error = 40;
    }

    if (combat_index == 5)
    {
        combat_hit_up = 64;
        combat_hit_down = 64;
        combat_hit_right = act_right ? 93 : 0;
        combat_hit_left = act_right ? 0 : 93;
        combat_damage = 15;
        combat_parry_error = 20;
    }

    combat_damage *= buff_combat_damage;

    // =================== Combat Attack Pattern ===================

    // On ground
    if (!combat_delay && combat_keytap && !crawl && !g_dash)
    {
        if (!hug_wall && !input->getButton(0))
        {
            if (!combat_combo_time && !combat_index)
            {
                combat_index = 1;
                combat_time = 15;
                combat_combo_time = 40;
                setEndLock(false);

                vel_x *= .8;
                vel_y = on_ground ? 0 : 1;
            }
            else if (!combat_time && combat_index == 1 && combat_combo_time)
            {
                combat_index = 2;
                combat_time = 15;
                combat_combo_time = 15;
                combat_delay = 35;
                setEndLock(false);

                vel_x *= .4;
                vel_y = on_ground ? 0 : 1;
            }
        }
        else if (!hug_wall && input->getButton(0))
        {
            if (!combat_combo_time && !combat_index)
            {
                combat_index = 4;
                combat_time = 15;
                combat_combo_time = 15;
                combat_delay = on_ground ? 40 : 70;
                setEndLock(false);

                vel_y = 3;
            }
        }
        else if (hug_wall)
        {
            if (!combat_combo_time && !combat_index)
            {
                combat_index = 5;
                combat_time = 12;
                combat_combo_time = 40;
                setEndLock(false);
            }
        }
    }

    // Charge Attack
    if (combat_charge_time > 0)
    {
        combat_index = 3;

        if (!combat_keyhold && combat_charge_time > 50)
        {
            combat_time = 10;
            combat_combo_time = 10;
            combat_delay = 150;

            setEndLock(false);
        }
    }

    if (!combat_delay && !combat_time && combat_keyhold &&
        !sprite_end_lock && !crawl && !hug_wall && !a_dash && !g_dash)
        combat_charge_time += buff_combat_speed;
    else
        combat_charge_time = 0;

    // std::cout << combat_keytap << " " << combat_keyhold << " " << combat_charge_time << "\n";
    // std::cout << combat_index << " " << combat_time << " " << combat_combo_time << "\n";
}

void Player::playerBlockCollision(std::vector<Block *> BlockVec)
{
    bool on_aleast_ground = false;
    bool hug_aleast_wall = false;
    bool crawl_lock_atleast = false;

    if (!crawl && !g_dash && !crawl_lock)
    {
        setHitWidth(58);
        setHitHeight(80);
        hit_offset_y = 0;
    }
    else
    {
        setHitWidth(78);
        setHitHeight(40);
        hit_offset_y = -20;
    }

    for (Block *block : BlockVec)
    {
        // If block is outside of play/usable view
        // No need to check for SHIT MAN i
        block->setOutBound(Camera::objectOutBound(this, block));
        if (block->getOutBound()) continue;

        // Collision Value
        int colli_x = abs(getHitX() - block->getX());
        int colli_y = abs(getHitY() - block->getY());
        int colli_y_stand = abs(getY() - block->getY());

        int hit_dist_x = (getHitWidth() + block->getHitWidth()) / 2;
        int hit_dist_y = (getHitHeight() + block->getHitHeight()) / 2;
        int hit_dist_y_stand = (80 + block->getHitHeight()) / 2;

        if (block->getSeeThru()) {
            if (colli_x + 10 < hit_dist_x && colli_y + 10 < hit_dist_y)
            {
                if (block->getSeeAlpha() > block->getSeeAlphaMin())
                    block->setSeeAlpha(block->getSeeAlpha() - 5);
            }
            else
            {
                if (block->getSeeAlpha() < 255)
                    block->setSeeAlpha(block->getSeeAlpha() + 5);
            } 
        }

        // If it a go thru block
        // No need hitbox detection
        if (block->getGoThru()) continue;

        block->setHugged(false);
        block->setStepOn(false);
        // Hit Left wall
        if (getHitX() < block->getX() && colli_x < hit_dist_x &&
            getHitY() < block->getY() + hit_dist_y - 10 &&
            getHitY() > block->getY() - hit_dist_y + 10)
        {
            if (can_hug_wall && !on_ground && !a_dash)
            {
                hug_aleast_wall = true;
                hug_wall_left = true;
                vel_x = 0;

                setX(block->getX() - hit_dist_x + 3);
                block->setHugged(-1);
            }
            else
            {
                setX(block->getX() - hit_dist_x);
                if (a_dash || g_dash)
                    vel_x = -vel_x * .5;
                act_right = 1;
            }

            continue;
        }

        // Hit Right wall
        if (getHitX() > block->getX() && colli_x < hit_dist_x &&
            getHitY() < block->getY() + hit_dist_y - 10 &&
            getHitY() > block->getY() - hit_dist_y + 10)
        {
            if (can_hug_wall && !on_ground && !a_dash)
            {
                hug_aleast_wall = true;
                hug_wall_right = true;
                vel_x = 0;
                
                setX(block->getX() + hit_dist_x - 3);
                block->setHugged(1);
            }
            else
            {
                setX(block->getX() + hit_dist_x);
                if (a_dash || g_dash)
                    vel_x = -vel_x * .5;
                act_right = 0;
            }

            continue;
        }

        // Ceiling logic
        if ((getHitX() < block->getX() + hit_dist_x) &&
            (getHitX() > block->getX() - hit_dist_x))
        {
            if (vel_y > 0 && getHitY() < block->getY() &&
                colli_y < hit_dist_y - vel_y)
            {
                ceiling_knockout = ceiling_knockout_delay;
                setY(block->getY() - block->getHeight() / 2 - 40 - vel_y);
                vel_y = -vel_y * 0.1;
                continue;
            }

            if (on_ground && getY() < block->getY() &&
                colli_y_stand < hit_dist_y_stand)
                crawl_lock_atleast = true;
        }

        // Stand on block
        if (!on_aleast_ground &&
            getHitY() > block->getY() &&
            colli_y < hit_dist_y &&
            (getHitX() < block->getX() + hit_dist_x) &&
            (getHitX() > block->getX() - hit_dist_x))
        {
            if (block->getVelX())
                setX(getX() + block->getVelX());
            if (block->getVelY())
                setY(getY() + block->getVelY());
            
            if (!crawl && !g_dash)
                setY(block->getY() + (block->getHeight() + getHitHeight()) / 2 - 1);

            block->setStepOn(true);

            on_aleast_ground = true;
            hug_wall_left = false;
            hug_wall_right = false;
            continue;
        }
    }

    on_ground = on_aleast_ground;
    crawl_lock = crawl_lock_atleast;
    if (!hug_aleast_wall)
    {
        hug_wall_left = false;
        hug_wall_right = false;
    }
}

void Player::playerEnemyCollision(std::vector<Enemy *> EnemyVec)
{
    for (Enemy *enemy : EnemyVec)
    {
        if (enemy->getDead()) continue;

    // ================== TAKING DAMAGE =======================
        int colli_x = abs(getHitX() - enemy->getX());
        int colli_y = abs(getHitY() - enemy->getY());
        int hit_dist_x = (getHitWidth() + enemy->getHitWidth()) / 2;
        int hit_dist_y = (getHitHeight() + enemy->getHitHeight()) / 2;

        if (!enemy->getDead() &&
            colli_x < hit_dist_x &&
            colli_y < hit_dist_y)
        {
            if (enemy->getCollideDamage())
                playerGetHit(enemy->getCollideDamage());

            // Addition enemy logic
            enemy->enemyPlayerCollision(this);
        }


    // ================== DEALING DAMAGE =======================
        if (weapon_equip && !(enemy->getInvinTime()) &&
            (combat_time || a_dash || g_dash))
        {
            if ((enemy->getX() > getHitX()? colli_x < combat_hit_right + enemy->getHitWidth() / 2 :
                                            colli_x < combat_hit_left  + enemy->getHitWidth() / 2) &&
                (enemy->getY() > getHitY()? colli_y < combat_hit_up    + enemy->getHitHeight() / 2 :
                                            colli_y < combat_hit_down  + enemy->getHitHeight() / 2))
            {
                enemy->enemyGetHit(combat_damage);

                if (a_dash || g_dash) vel_x = -vel_x;
            }
        }
    }
}

void Player::playerGetHit(int dmg)
{
    if (invulnerable_time || invincible_time) return;
    invulnerable_time = invulnerable_time_max;
    hp -= dmg;
}

void Player::playerDeveloper(Input *input)
{
    int vel_developer = input->getButton(5) ? 20 : 4;
    if (input->getButton(0)) setY(getY() + vel_developer);
    if (input->getButton(1)) setY(getY() - vel_developer);
    if (input->getButton(3)) setX(getX() + vel_developer);
    if (input->getButton(2)) setX(getX() - vel_developer);
}

void Player::playerGrid(SDL_Renderer *renderer)
{
    // Really sorry but grid straight up dont work in other scale mode
    // Im not doing the math bruh
    if (grid)
    {
        // Draw grid line
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        int gridLineX = unfocus_x ? 0 : int(getX()) % 64;
        int gridLineY = unfocus_y ? 0 : int(getY()) % 64 + 28;

        for (int i = 0; i < int(Game::WIDTH / 64); i++)
        {
            int drawGridX = i * 64 - gridLineX;
            int camX = Camera::playerShiftX(this);
            SDL_RenderDrawLine(renderer, drawGridX + camX, 0,
                                drawGridX + camX, Game::HEIGHT);
        }
        for (int i = 0; i < int(Game::HEIGHT / 64); i++)
        {
            int camY = Camera::playerShiftY(this);
            int drawGridY = Game::HEIGHT - i * 64 + gridLineY;
            SDL_RenderDrawLine(renderer, 0, drawGridY + camY,
                                Game::WIDTH, drawGridY + camY); 
        }
    }
}

// ==== Note ====
// Reason for the absence of player sprite in update
// is to avoid a lag in drawing other decoration/block layer caused
// by intensive <player> calculation
void Player::playerUpdate(SDL_Renderer *renderer, Map *map, Input *input)
{
    if (!godmode)
    {
        playerMovement(input);
        playerCombat(map, input);
        playerBlockCollision(map->BlockVec);
        playerEnemyCollision(map->EnemyVec);
    }
    else
        playerDeveloper(input);

    playerCameraProperty(input);
    playerDrawProperty();

    // ===============DEVELOPER input===============
    // GODMODE
    if (input->getButton(10) && !godmode_hold)
    {
        godmode_hold = true;
        godmode = godmode ? false : true;
    }
    if (!input->getButton(10)) godmode_hold = false;

    // DISPLAY GRID
    if (input->getButton(9) && !grid_hold)
    {
        grid_hold = true;
        grid = grid ? false : true;
    };
    if (!input->getButton(9)) grid_hold = false;
}

void Player::playerEnableAllMoveset()
{
    can_move = true;
    can_jump = true;
    can_crawl = true;
    can_g_dash = true;
    can_a_dash = true;
    can_hug_wall = true;
}