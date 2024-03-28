#include <player.h>
#include <map.h>

// Constructor
Player::Player(float X, float Y, int w, int h, int hw, int hh, int sim, int sfm, int si, int sf) :
    Object2D(X, Y, w, h, hw, hh) {}

// Fuck her 2nite
void Player::initPlayer(SDL_Renderer *renderer)
{
    // Nakuru normal mvoement
    PlayerRight = Sprite::loadTexture(renderer, "res/NakuSheet/NakuRight.png");
    PlayerLeft = Sprite::loadTexture(renderer, "res/NakuSheet/NakuLeft.png");

    // Nakuru holding weapon
    PlayerRightWeapon = Sprite::loadTexture(renderer, "res/NakuSheet/NakuRightWeapon.png");
    PlayerLeftWeapon = Sprite::loadTexture(renderer, "res/NakuSheet/NakuLeftWeapon.png");

    // Nakuru Squid Game
    PlayerSquid = Sprite::loadTexture(renderer, "res/NakuSheet/NakuSquid.png");

    // EXPERIMENTATION  hitbox = Sprite::loadTexture(renderer, "res/HitboxMyass.png");
    combatbox = Sprite::loadTexture(renderer, "res/CombatMyass.png");
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
bool Player::getIsMove() { return getVelX(); }
bool Player::getIsJump() { return getVelY(); }
bool Player::getIsGDash() { return g_dash; }
bool Player::getIsADash() { return a_dash; }
bool Player::getIsCrawl() { return crawl; }
bool Player::getIsHugWall() { return hug_wall_left || hug_wall_right; }

bool Player::getCanHugWall() { return can_hug_wall; }

void Player::setCanMove(bool can) { can_move = can; }
void Player::setCanJump(bool can) { can_jump = can; }
void Player::setCanCrawl(bool can) { can_crawl = can; }
void Player::setCanGDash(bool can) { can_g_dash = can; }
void Player::setCanADash(bool can) { can_a_dash = can; }
void Player::setCanHugWall(bool can) { can_hug_wall = can; }

void Player::setHugWallLeft(bool hwl) { hug_wall_left = hwl; }
void Player::setHugWallRight(bool hwr) { hug_wall_right = hwr; }

// Movement
int Player::getAirCur() { return air_cur; }
int Player::getAirMax() { return air_max; }
int Player::getDecel() { return decel_x; }
bool Player::getSuperJump() { return jump_super >= jump_super_max; }

// Action speak louder than word
// "Going to the mall is louder than... green?"
int Player::getActIndex() { return act_index; }
bool Player::getActRight() { return act_right; }
void Player::setActRight(bool ar) { act_right = ar; }

// Combat / Hitbox
int Player::getHpCur() { return hp; }
int Player::getHpMax() { return hp_max; }

int Player::getHitX() { return getX() + hit_offset_x; }
int Player::getHitY() { return getY() + hit_offset_y; }

bool Player::getWeaponEquip() { return weapon_equip; }
int Player::getInvincibleTime() { return invincible_time; }
int Player::getInvulnerableTime() { return invulnerable_time; }

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

// Uncategorized
void Player::setOnGround(bool og) { on_ground = og; }
bool Player::getOnGround() { return on_ground; }
void Player::setCrawlLock(bool cl) { crawl_lock = cl; }
void Player::setCeilingKnockout(int cko) { ceiling_knockout = cko; }
void Player::setBuffJumpTime(int bjt) { buff_jump_time = bjt; }

// Other Method

void Player::playerDrawSprite(SDL_Renderer *renderer)
{
    objectSetSprite(sprite_end_lock);

    int drawX = Game::WIDTH / 2 + (offset_mid_x - sprite_size*2) * camera_scale
                + Camera::playerShiftX(this); 
    int drawY = Game::HEIGHT / 2 - (offset_mid_y + sprite_size*2) * camera_scale
                + Camera::playerShiftY(this);


    SDL_Rect desRect = {drawX, drawY,
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
    act_right = getVelX() > .2 ? 1 : getVelX() < -.2 ? 0 : act_right;

    // Ow< ouch
    if (invulnerable_time > invulnerable_time_max * .8)
    {
        setAct(8, act_right);
        setSprite(1, 0);
        return;
    }

    // Movement
    if (!combat_index)
    {
        if (abs(getVelX()) <= .2)
        {
            // Idling
            setAct(0, act_right);
            setSprite(2, 64);
        }
        else
        {
            // Moving
            setAct(1, act_right);
            setSprite(8, 30 - abs(getVelX()) * 4);
        }

        // Decelerating
        if (decel_x != 0)
        {
            setAct(2, decel_x > 0);
            setSprite(2, 2);
        }

        // Jumping
        if (getVelY() > .2 && !on_ground)
        {
            setAct(3, act_right);
            setSprite(4, 16);
        }
        if (getVelY() < .2 && !on_ground)
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
            setSprite((abs(getVelX()) > 0 ? 4 : 1), 8);
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
                setSprite(getVelX() ? 4 : 1, 30 - abs(getVelX()) * 4);
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
        setEndLock(false);
    }

    if (!a_dash && !g_dash && !weapon_equip_delay && !combat_index)
        setEndLock(false);

    // ============= SET SPRITE ==============

    playerCurrentTexture = act_right ? 
        (weapon_equip ? PlayerRightWeapon : PlayerRight) :
        (weapon_equip ? PlayerLeftWeapon : PlayerLeft);

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
        ease_x -= abs(getVelX() / 5);
    if (!act_right &&
        ease_x < 64 * (weapon_equip ? 1 : 1.5))
        ease_x += abs(getVelX() / 5);
    if (!getVelX() && ease_x) ease_x -= ease_x / 100;

    // Look vertical up and down
    float vt_max = vertical_ahead_max;
    if (on_ground && !getVelX() &&
        vertical_ahead_time > vertical_ahead_time_max)
    {
        if (input->getButton(0) &&
            vertical_ahead < vt_max &&
            !(  unfocus_direction_y == 1 &&
                getY() > unfocus_offset_y - vt_max))
            vertical_ahead += (vt_max - abs(vertical_ahead)) / 30;
        if (input->getButton(1) &&
            vertical_ahead > -vt_max &&
            !(  unfocus_direction_y == -1 &&
                getY() < unfocus_offset_y + vt_max))
            vertical_ahead -= (vt_max - abs(vertical_ahead)) / 30;

        vertical_ahead = vertical_ahead > vt_max ? vt_max : vertical_ahead;
        vertical_ahead = vertical_ahead < -vt_max ? -vt_max : vertical_ahead;
    }

    if (on_ground && !getVelX() && !unfocus_y &&
        (input->getButton(0) || input->getButton(1)))
        vertical_ahead_time ++;
    else 
        vertical_ahead_time = 0;

    if ((!input->getButton(0) && vertical_ahead > 0) ||
        (!input->getButton(1) && vertical_ahead < 0))
        vertical_ahead -= vertical_ahead / 40;

    if (a_dash || g_dash)
    {
        effect_x += getVelX() > 0 ? -2 : 2;
        effect_x = effect_x > 64 ? 64 : effect_x;
        effect_x = effect_x <-64 ?-64 : effect_x;
    }
    else if (effect_x)
        effect_x -= effect_x / 40;
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

            if (getVelX() > 1)
            {
                decel_x = 1;
                setVelX(getVelX() - getAccelX() * 2.5);
            }
            else
            {
                decel_x = 0;
                setVelX(getVelX() - getAccelX());
            }
        }

        if (input->getButton(3) && !hug_wall_left)
        {
            if (hug_wall_right)
            {
                hug_wall_right = false;
                setX(getX() + 4);
            }

            if (getVelX() < -1)
            {
                decel_x = -1;
                setVelX(getVelX() + getAccelX() * 2.5);
            }
            else
            {
                decel_x = 0;
                setVelX(getVelX() + getAccelX());
            }
        }
    }

    // Crawling
    crawl = can_crawl && input->getButton(1) && on_ground && !g_dash && !decel_x && !g_dash_delay && abs(getVelX()) < vel_x_max / 2;
    crawl = crawl_lock || crawl;

    if (crawl && input->getButton(2) && !g_dash)
        setVelX(-vel_crawl);
    if (crawl && input->getButton(3) && !g_dash)
        setVelX(vel_crawl);

    // Deceleration
    if ((!input->getButton(2) && decel_x == 1) ||
        (!input->getButton(3) && decel_x == -1))
        decel_x = 0;

    if (!input->getButton(2) && !input->getButton(3) && !g_dash && !a_dash)
    {
        if (abs(getVelX()) >= getAccelX())
        {
            int direction = (getVelX() < 0 ? 1 : -1);
            setVelX(getVelX() + getAccelX() * direction);
        }
        else
            setVelX(0);
    }

    // Ground dash (more like sliding but whatever)
    if (can_g_dash && input->getButton(5) && !g_dash_delay &&
        !combat_index && !weapon_equip_frame &&
        on_ground && !g_dash && !crawl_lock && !a_dash)
    {
        g_dash = true;
        g_dash_delay = g_dash_delay_max * (crawl ? 1.5 : 1);
    }

    // Air dash
    if (can_a_dash && input->getButton(5) && !a_dash_delay &&
        !combat_index && !weapon_equip_frame &&
        !on_ground && !hug_wall && !crawl && !g_dash && getVelX() && air_cur && !jump_keyhold)
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

        setVelY(1 + 40 / (air_max - air_cur + 8));
        if (jump_super == jump_super_max)
            setVelY(7.3);

        // Wall jump
        if (!hug_wall)
            air_cur--;
        if (hug_wall_left)
        {
            setVelX(-10);
            setVelY(4);
            setX(getX() - getHitWidth() / 2);
        }
        if (hug_wall_right)
        {
            setVelX(10);
            setVelY(4);
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
                (combat_charge_time ? .8 : 1);
    // Acceleration x
    setAccelX( on_ice ? accel_x_ice : accel_x_ground);
    setAccelX(  getAccelX() *
                (weapon_equip ? .8 : 1) *
                (combat_charge_time ? .8 : 1));
    // Acceleration y
    setAccelY(jump_keyhold ? accel_hold : accel_tap);
    setAccelY(  getAccelY() *
                (weapon_equip ? 1.2 : 1) *
                (combat_charge_time ? 1.2 : 1));

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
        if (getVelX() < -vel_x_max)
            setVelX(-vel_x_max);
        if (getVelX() > vel_x_max)
            setVelX(vel_x_max);
    }
    
    setX(getX() + getVelX());

    // Vertigo is a bad map
    if (getVelY() < 0)
        setAccelY(accel_tap);

    if (on_ground)
        setVelY(0);
    else if (hug_wall_left || hug_wall_right)
        setVelY(-1);
    else
        setVelY(getVelY() + getAccelY());

    // Terminal Velocity
    if (getVelY() < vel_terminal)
        setVelY(vel_terminal);

    // SUPER JUMP
    if (crawl && !crawl_lock && !getVelX())
        jump_super += jump_super < jump_super_max;
    else
        jump_super = 0;

    // Ground dash
    if (g_dash)
    {
        g_dash_frame++;
        setVelX(g_dash_vel * (act_right ? 1 : -1) * (crawl ? 1.4 : 1));
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
        setVelX(
            (3 + 90 / (air_max - air_cur + 6)) * 
            (getVelX() > 0 ? 1 : -1)
        );
        setVelY(0);

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

    setY(getY() + getVelY());
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
            PlayerSquid, getX(), getY(),
            16, 16, 32, 32,
            act_right * 2 - 1, getVelY() + 10, 0, -.2,
            10, 1000, -1,
            1, 0, 0,
            4, 10
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
            setVelX(0);
            setVelY(0);

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

    if (!weapon_equip || weapon_equip_frame) return;

    // =================== Combat hitbox handler ===================
    if (!combat_time && !a_dash && !g_dash)
    {
        setCombatHitU(0);
        setCombatHitD(0);
        setCombatHitL(0);
        setCombatHitR(0);
        setCombatDamage(0);
        combat_parry_error = 10;
    }

    if (a_dash)
    {
        setCombatHitU(30);
        setCombatHitD(30);
        setCombatHitR(act_right ? 80 : 0);
        setCombatHitL(act_right ? 0 : 80);
        setCombatDamage(10);
    }

    if (g_dash)
    {
        setCombatHitU(20);
        setCombatHitD(20);
        setCombatHitR(act_right ? 100 : 0);
        setCombatHitL(act_right ? 0 : 100);
        setCombatDamage(crawl ? 20 : 12);
    }

    if (combat_index == 1)
    {
        setCombatHitU(40);
        setCombatHitD(40);
        setCombatHitR(act_right ? 100 : 0);
        setCombatHitL(act_right ? 0 : 100);
        setCombatDamage(10);
        combat_parry_error = 3;
    }

    if (combat_index == 2)
    {
        setCombatHitU(15);
        setCombatHitD(15);
        setCombatHitL(act_right ? 0 : 120);
        setCombatHitR(act_right ? 120 : 0);
        setCombatDamage(20);
        combat_parry_error = 1;
    }

    if (combat_index == 3)
    {
        setCombatHitU(80);
        setCombatHitD(60);
        setCombatHitL(act_right ? 0 : 130);
        setCombatHitR(act_right ? 130 : 0);
        setCombatDamage(30);
        combat_parry_error = 0;
    }

    if (combat_index == 4)
    {
        setCombatHitU(76);
        setCombatHitD(0);
        setCombatHitL(64);
        setCombatHitR(64);
        setCombatDamage(15);
        combat_parry_error = 40;
    }

    if (combat_index == 5)
    {
        setCombatHitU(64);
        setCombatHitD(64);
        setCombatHitL(act_right ? 0 : 93);
        setCombatHitR(act_right ? 93 : 0);
        setCombatDamage(15);
        combat_parry_error = 20;
    }

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

                setVelX(getVelX() * .8);
                setVelY(on_ground ? 0 : 1);
            }
            else if (!combat_time && combat_index == 1 && combat_combo_time)
            {
                combat_index = 2;
                combat_time = 15;
                combat_combo_time = 15;
                combat_delay = 35;
                setEndLock(false);

                setVelX(getVelX() * .4);
                setVelY(on_ground ? 0 : 1);
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

                setVelY(3);
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

void Player::playerHitBox()
{
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
}

void Player::playerGetHit(Map *map, int dmg)
{
    if (invulnerable_time || invincible_time) return;

    map->ParticleBackVec.push_back(new ParticleEffect(
        Sprite::loadTexture(map->Renderer, "res/ParticleSheet/BloodSplatter.png"),
        getX(), getY(), 600, 600,
        100, 100, 6, 2, 4, 0
    ));

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

        std::cout << int(getX() / 64) << " " << int(getY() / 64) << "\n";
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
        playerHitBox();
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