#include "player.h"
#include "map.h"

// Constructor
Player::Player(float X, float Y, int w, int h, int hw, int hh, int sim, int sfm, int si, int sf) : Object2D(X, Y, w, h, hw, hh, sim, sfm, si, sf) {}

// Fuck her 2nite
void Player::initPlayer(SDL_Renderer *renderer)
{
    // Initialize input
    for (int i = 0; i < 11; i++)
        button.push_back(false);

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
void Player::setVelX(float X)
{
    vel_x = X;
}
void Player::setVelY(float Y)
{
    vel_y = Y;
}
void Player::setAct(int index, bool right)
{
    if (act_index != index || act_right != right)
    {
        act_index = index;
        act_right = right;
    }
}

void Player::setSprite(int m_index, int m_frame)
{
    setSprFrameMax(m_frame);
    setSprIndexMax(m_index);
}

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

void Player::setFocusXCondition(FocusXCondition fcond)
{
    fxcondition = fcond;
}

void Player::setFocusYCondition(FocusYCondition fcond)
{
    fycondition = fcond;
}

void Player::setFocus()
{
    auto resultX = fxcondition(getX(), getY());
    offset_x = FocusGet(resultX, 0);
    focus_x = FocusGet(resultX, 1);

    auto resultY = fycondition(getX(), getY());
    offset_y = FocusGet(resultY, 0);
    focus_y = FocusGet(resultY, 1);
}

void Player::setCanMove(bool can)
{
    can_move = can;
}
void Player::setCanJump(bool can)
{
    can_jump = can;
}
void Player::setCanCrawl(bool can)
{
    can_crawl = can;
}
void Player::setCanGDash(bool can)
{
    can_g_dash = can;
}
void Player::setCanADash(bool can)
{
    can_a_dash = can;
}
void Player::setCanHugWall(bool can)
{
    can_hug_wall = can;
}

void Player::setCombatDelay(float delay)
{
    combat_delay = delay;
}

void Player::setInvincibleTime(int time)
{
    invincible_time = time;
}

// Getter
float Player::getVelX()
{
    return vel_x;
}
float Player::getVelY()
{
    return vel_y;
}
bool Player::getSuperJump()
{
    return jump_super >= jump_super_max;
}
// Action speak louder than word
// "Going to the mall is louder than... green?"
int Player::getActIndex()
{
    return act_index;
}
bool Player::getActRight()
{
    return act_right;
}
int Player::getDecel()
{
    return decel_x;
}
int Player::getHitX()
{
    return getX() + hit_offset_x;
}
int Player::getHitY()
{
    return getY() + hit_offset_y;
}

int Player::getAirCur()
{
    return air_cur;
}
int Player::getAirMax()
{
    return air_max;
}
int Player::getHpCur()
{
    return hp;
}
int Player::getHpMax()
{
    return hp_max;
}

int Player::getInvincibleTime()
{
    return invincible_time;
}
int Player::getInvurnableTime()
{
    return invurnable_time;
}

bool Player::getWeaponEquip()
{
    return weapon_equip;
}
int Player::getCombatHitU()
{
    return combat_hit_up;
}
int Player::getCombatHitD()
{
    return combat_hit_down;
}
int Player::getCombatHitL()
{
    return combat_hit_left;
}
int Player::getCombatHitR()
{
    return combat_hit_right;
}
float Player::getCombatTime()
{
    return combat_time;
}
float Player::getCombatDelay()
{
    return combat_delay;
}
float Player::getCombatParryError()
{
    return combat_parry_error;
}

// Focus Offset Stuff
// Idk how to explain
bool Player::getFocusX()
{
    return focus_x;
}
bool Player::getFocusY()
{
    return focus_y;
}
int Player::getOffsetX()
{
    return offset_x;
}
int Player::getOffsetY()
{
    return offset_y;
}

bool Player::getIsMove()
{
    return vel_x;
}
bool Player::getIsJump()
{
    return vel_y;
}
bool Player::getIsGDash()
{
    return g_dash;
}
bool Player::getIsADash()
{
    return a_dash;
}
bool Player::getIsCrawl()
{
    return crawl;
}
bool Player::getIsHugWall()
{
    return hug_wall_left || hug_wall_right;
}

// Other Method

void Player::playerDrawSprite(SDL_Renderer *renderer)
{
    // Camera focus or not
    setFocus();
    if (getSprFrame() < getSprFrameMax())
        setSprFrame(getSprFrame() + 1);
    else
    {
        setSprFrame(0);
        setSprIndex(getSprIndex() + 1);
    }

    if (getSprIndex() >= getSprIndexMax())
        if (sprite_end_lock)
            setSprIndex(getSprIndexMax() - 1);
        else
            setSprIndex(0);

    int drawX = focus_x ? Game::WIDTH / 2 : getX();
    int drawY = focus_y ? Game::HEIGHT / 2 - 1 : Game::HEIGHT - 1 - getY();

    SDL_Rect desRect = {drawX - sprite_size * 2, drawY - sprite_size * 2, sprite_size * 4, sprite_size * 4};
    SDL_Rect srcRect = {getSprIndex() * sprite_size, act_index * sprite_size, sprite_size, sprite_size};

    if (!invurnable_time)
        SDL_SetTextureAlphaMod(playerCurrentTexture, 255);
    SDL_RenderCopy(renderer, playerCurrentTexture, &srcRect, &desRect);
}

void Player::playerSpriteIndex()
{
    // Set index and stuff
    act_right = vel_x > .2 ? 1 : vel_x < -.2 ? 0 : act_right;

    if (invurnable_time > invurnable_time_max * .8)
    {
        setAct(8, act_right);
        setSprite(1, 0);
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
                setSprite(4, 2);
            }
        }
    }

    // Weapon draw
        if (weapon_equip_delay && weapon_equip)
        {
            setAct(9, act_right);
            setSprite(8, 3);
            setEndLock(true);
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

bool Player::playerInput(SDL_GameController *controller)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                return true;
                break;
            case SDLK_w:
                button[0] = true;
                break;
            case SDLK_s:
                button[1] = true;
                break;
            case SDLK_a:
                button[2] = true;
                break;
            case SDLK_d:
                button[3] = true;
                break;
            case SDLK_SPACE:
                button[4] = true;
                break;
            case SDLK_LSHIFT:
                button[5] = true;
                break;
            case SDLK_l:
                button[6] = true;
                break;
            case SDLK_q:
                button[7] = true;
                break;
            case SDLK_e:
                button[8] = true;
                break;
            case SDLK_g:
                button[9] = true;
                break;
            case SDLK_h:
                button[10] = true;
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_w:
                button[0] = false;
                break;
            case SDLK_s:
                button[1] = false;
                break;
            case SDLK_a:
                button[2] = false;
                break;
            case SDLK_d:
                button[3] = false;
                break;
            case SDLK_SPACE:
                button[4] = false;
                break;
            case SDLK_LSHIFT:
                button[5] = false;
                break;
            case SDLK_l:
                button[6] = false;
                break;
            case SDLK_q:
                button[7] = false;
                break;
            case SDLK_e:
                button[8] = false;
                break;
            case SDLK_g:
                button[9] = false;
                break;
            case SDLK_h:
                button[10] = false;
                break;
            }
            break;
        case SDL_CONTROLLERBUTTONDOWN:
            switch (event.cbutton.button)
            {
            case SDL_CONTROLLER_BUTTON_DPAD_UP:
                button[0] = true;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                button[1] = true;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                button[2] = true;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                button[3] = true;
                break;
            case SDL_CONTROLLER_BUTTON_A:
                button[4] = true;
                break;
            case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
                button[5] = true;
                break;
            case SDL_CONTROLLER_BUTTON_X:
                button[6] = true;
                break;
            case SDL_CONTROLLER_BUTTON_Y:
                button[7] = true;
                break;
            case SDL_CONTROLLER_BUTTON_B:
                button[8] = true;
                break;
            }
            break;
        case SDL_CONTROLLERBUTTONUP:
            switch (event.cbutton.button)
            {
            case SDL_CONTROLLER_BUTTON_DPAD_UP:
                button[0] = false;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                button[1] = false;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                button[2] = false;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                button[3] = false;
                break;
            case SDL_CONTROLLER_BUTTON_A:
                button[4] = false;
                break;
            case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
                button[5] = false;
                break;
            case SDL_CONTROLLER_BUTTON_X:
                button[6] = false;
                break;
            case SDL_CONTROLLER_BUTTON_Y:
                button[7] = false;
                break;
            case SDL_CONTROLLER_BUTTON_B:
                button[8] = false;
                break;
            }
            break;
        }
    }

    return false;    
}

void Player::playerMovement()
{

    bool hug_wall = hug_wall_left || hug_wall_right;

    // ===============Main input===============

    // Moving L/R
    if (can_move && !g_dash && !a_dash && !crawl)
    {
        if (button[2] && !hug_wall_right)
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

        if (button[3] && !hug_wall_left)
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
    crawl = can_crawl && button[1] && on_ground && !g_dash && !decel_x && !g_dash_delay && abs(vel_x) < vel_x_max / 2;
    crawl = crawl_lock || crawl;

    if (crawl && button[2] && !g_dash)
        vel_x = -vel_crawl;
    if (crawl && button[3] && !g_dash)
        vel_x = vel_crawl;

    // Deceleration
    if ((!button[2] && decel_x == 1) ||
        (!button[3] && decel_x == -1))
        decel_x = 0;

    if (!button[2] && !button[3] && !g_dash && !a_dash)
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
    if (can_g_dash && button[5] && !g_dash_delay && !combat_index && on_ground && !g_dash && !crawl_lock && !a_dash)
    {
        g_dash = true;
        g_dash_delay = g_dash_delay_max * (crawl ? 1.5 : 1);
    }

    // Air dash
    if (can_a_dash && button[5] && !a_dash_delay && !combat_index && !on_ground && !hug_wall && !crawl && !g_dash && vel_x != 0 && air_cur > 0 && !jump_keyhold)
    {
        a_dash = true;
        air_cur--;
        a_dash_delay = a_dash_delay_max;
    }

    // Jump held key
    if (can_jump && button[4] && !jump_keyhold && (air_cur > 0 || hug_wall) &&
        !g_dash && !a_dash && !decel_x && !crawl_lock && !ceiling_knockout)
    {
        setY(getY() + 10);
        on_ground = false;

        vel_y = 1 + 40 / (air_max - air_cur + 8);
        if (jump_super == jump_super_max)
            vel_y = 7;

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
    if (!button[4])
    {
        jump_keyhold = false;
    }

    // Buff Combat
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
    vel_x_max *= weapon_equip ? .8 : 1;
    vel_x_max *= buff_move;
    // Acelecreaitm
    accel_x = on_ice ? accel_x_ice : accel_x_ground;
    accel_x *= weapon_equip ? .8 : 1;
    accel_x *= buff_move;
    accel_y = jump_keyhold ? accel_hold : accel_tap;
    accel_y *= weapon_equip ? 1.2 : 1;
    accel_y /= buff_jump;
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
    if (crawl && vel_x == 0)
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

void Player::playerCombat(Map *map)
{
// ===================== COMBAT (VERY LEGENDARY) ====================
    bool hug_wall = hug_wall_left || hug_wall_right;

    // Buff Combat
    if (buff_combat_speed_time)
        buff_combat_speed_time--;
    else
        buff_combat_speed = 1;
    
    if (buff_combat_damage_time)
        buff_combat_damage_time--;
    else
        buff_combat_damage = 1;

    // Weapon equipment
    if (button[7] && !weapon_equip_delay && !weapon_equip_keyhold &&
        on_ground && vel_x == 0)
    {
        weapon_equip_keyhold = true;
        weapon_equip_delay = weapon_equip_delay_max;
        weapon_equip = weapon_equip ? false : true;
    };
    if (!button[7]) weapon_equip_keyhold = false;

    // Weapon draw delay
    if (weapon_equip_delay > 0)
        weapon_equip_delay -= buff_combat_speed;

    // Attack pattern (really fucking sophisicated)

    if (button[6])
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

    if (button[8] && !jelly_keyhold)
    {
        jelly_keyhold = true;
        map->ProjectileVec.push_back(new Projectile(
            PlayerSquid->getTexture(), getX(), getY(), 16, 16, 32, 32, act_right * 2 - 1, vel_y + 10, 0, -.2, 10, 1000, -1, 1, 1, 0, 4, 10
        ));
    }
    
    if (!button[8] && jelly_keyhold)
        jelly_keyhold = false;

    // Invincibility frame
    if (invincible_time)
        invincible_time--;

    if (invurnable_time) {
        invurnable_time--;
        if (invurnable_time > invurnable_time_max * .8)
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
        SDL_SetTextureAlphaMod(playerCurrentTexture, (invurnable_time % 15 > 0) ? 200 : 160);
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
        combat_hit_right = act_right ? 100 : 0;
        combat_hit_left = act_right ? 0 : 100;
        combat_damage = 30;
        combat_parry_error = 0;
    }

    // =================== Combat Attack Pattern ===================

    // On ground
    if (!combat_delay && combat_keytap && !hug_wall && !crawl && !g_dash && on_ground)
    {
        if (!button[0])
        {
            if (!combat_combo_time && !combat_index)
            {
                combat_index = 1;
                combat_time = 15;
                combat_combo_time = 40;

                setEndLock(false);

                vel_x *= .8;
            }
            else if (!combat_time && combat_index == 1 && combat_combo_time)
            {
                combat_index = 2;
                combat_time = 15;
                combat_combo_time = 35;

                setEndLock(false);

                vel_x *= .4;
            }
        }
        else
        {
            if (!combat_combo_time && !combat_index)
            {
                std::cout << "upward attack \n";
                combat_index = 4;
                combat_time = 15;
                combat_combo_time = 40;

                setEndLock(false);
            }
        }
    }

    // Charge Attack
    if (!combat_delay && combat_charge_time > 0)
    {
        combat_index = 3;

        if (!combat_keyhold && combat_charge_time > 50)
        {
            combat_time = 10;
            combat_combo_time = 10;
            combat_delay = 100;

            setEndLock(false);
        }
    }

    if (!combat_delay && combat_keyhold && !crawl && !hug_wall && !a_dash && !g_dash)
        combat_charge_time++;
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
        // Collision Value
        int colli_x = abs(getHitX() - block->getX());
        int colli_y = abs(getHitY() - block->getY());
        int colli_y_stand = abs(getY() - block->getY());

        // If block is outside of play/usable view
        // No need to check for SHIT MAN
        block->setOutBound((
            colli_x - block->getWidth() / 2 > Game::WIDTH ||
            colli_y - block->getHeight() / 2 > Game::HEIGHT
        ));
        if (block->getOutBound()) continue;

        int hit_dist_x = (getHitWidth() + block->getHitWidth()) / 2;
        int hit_dist_y = (getHitHeight() + block->getHitHeight()) / 2;
        int hit_dist_y_stand = (80 + block->getHitHeight()) / 2;

        if (block->getSeeThru()) {
            if (colli_x + 10 < hit_dist_x && colli_y + 10 < hit_dist_y)
            {
                if (block->getSeeAlpha() > 15)
                    block->setSeeAlpha(block->getSeeAlpha() - 10);
            }
            else
            {
                if (block->getSeeAlpha() < 255)
                    block->setSeeAlpha(block->getSeeAlpha() + 10);
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
            {
                playerGetHit(enemy->getCollideDamage());
            }

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
    if (invurnable_time || invincible_time) return;
    Audio::playSFX("res/Audio/SFX/NakuHurt.wav", -1);

    invurnable_time = invurnable_time_max;
    hp -= dmg;
}

void Player::playerDeveloper()
{
    int vel_developer = button[5] ? 20 : 4;
    if (button[0]) setY(getY() + vel_developer);
    if (button[1]) setY(getY() - vel_developer);
    if (button[3]) setX(getX() + vel_developer);
    if (button[2]) setX(getX() - vel_developer);
}

void Player::playerGrid(SDL_Renderer *renderer)
{
    if (grid)
    {
        // Draw grid line
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        int gridLineX = getX() / 64;
        int gridLineY = getY() / 64;

        for (int i = gridLineX - 11; i < gridLineX + 11; i++)
        {
            int drawGridX = focus_x ? i * 64 + offset_x - getX() : i * 64; 
            SDL_RenderDrawLine(renderer, drawGridX, 0, drawGridX, Game::HEIGHT);
        }
        for (int i = gridLineY - 6; i < gridLineY + 6; i++)
        {
            int drawGridY = focus_y ? i * 64 + offset_y - getY() : i * 64;
            SDL_RenderDrawLine(renderer, 0, 720 - drawGridY, Game::WIDTH, 720 - drawGridY); 
        }

        /*
        console.log printf print std::cout
        System.out.println puts echo fmt.Println
        Console.WriteLine println putStrLn
        Write-Output SELECT io.write Debug.Print
        disp cat tex.print NSLog WScript.Echo
        DISPLAY Put_Line format t write writeln
        DBMS_OUTPUT.PUT_LINE Transcript show:
        Debug.log putStr MsgBox io:format
        Write to Measurement File

        of the <grid position> ('w')
        */
        // std::cout << int(getX() / 64) << " " << int(getY() / 64) << "\n";

        int drawBoxX = focus_x ? Game::WIDTH / 2 : getHitX();
        int drawBoxY = focus_y ? Game::HEIGHT / 2 - 1 : Game::HEIGHT - 1 - getHitY();
        int boxWidth = combat_hit_left + combat_hit_right;
        int boxHeight = combat_hit_up + combat_hit_down;
        SDL_Rect boxRect = {drawBoxX - (boxWidth/2 - combat_hit_left > combat_hit_right ? combat_hit_right : combat_hit_left),
                            drawBoxY - (boxHeight/2 - combat_hit_up > combat_hit_down ? combat_hit_down : combat_hit_up),
                            boxWidth, boxHeight};
        SDL_RenderCopy(renderer, combatbox->getTexture(), NULL, &boxRect);

        SDL_Rect hitRect = {drawBoxX - 5, drawBoxY - 5, 10, 10};
        SDL_RenderCopy(renderer, hitbox->getTexture(), NULL, &hitRect);
    }
}

// ==== Note ====
// Reason for the absence of player sprite in update
// is to avoid a lag in drawing other decoration/block layer caused
// by intensive <player> calculation
void Player::playerUpdate(SDL_Renderer *renderer, Map *map)
{
    if (!godmode)
    {
        playerMovement();
        playerCombat(map);
        playerBlockCollision(map->BlockVec);
        playerEnemyCollision(map->EnemyVec);
    }
    else
    {
        playerDeveloper();
    }

    playerSpriteIndex();

    // ===============DEVELOPER input===============
    // GODMODE
    if (button[10] && !godmode_hold)
    {
        godmode_hold = true;
        godmode = godmode ? false : true;
    }
    if (!button[10]) godmode_hold = false;

    // DISPLAY GRID
    if (button[9] && !grid_hold)
    {
        grid_hold = true;
        grid = grid ? false : true;
    };
    if (!button[9]) grid_hold = false;
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