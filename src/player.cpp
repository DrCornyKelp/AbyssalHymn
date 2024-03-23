#include "player.h"
#include "map.h"

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

    // FUNNNNN
    PlayerParryEffect = new Sprite(64, 64, 1, "res/NakuSheet/NakuParryEffect.png");
    PlayerParryEffect->setTexture(Sprite::loadTexture(renderer, PlayerParryEffect->getSpritePath()));

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

void Player::setCombatDelay(int delay)
{
    combat_delay = delay;
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
int Player::getCombatTime()
{
    return combat_time;
}
int Player::getCombatDelay()
{
    return combat_delay;
}

Sprite *Player::getPlayerParrySprite()
{
    return PlayerParryEffect;
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

    if (!invincible_time) 
        SDL_SetTextureAlphaMod(playerCurrentTexture, 255);
    SDL_RenderCopy(renderer, playerCurrentTexture, &srcRect, &desRect);
}

void Player::playerSpriteIndex()
{
    // Set index and stuff
    act_right = vel_x > .2 ? 1 : vel_x < -.2 ? 0 : act_right;

    if (invincible_time > invincible_time_max * .8)
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
            setSprite(8, 2);
            setEndLock(true);
        }

        if (combat_index == 2 && combat_time)
        {
            setAct(11, act_right);
            setSprite(8, 2);
            setEndLock(true);
        }

        if (combat_index == 3)
        {
            setAct(12, act_right);
            setSprite(combat_keyhold ? 1 : 4, 2);
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

void Player::playerInput()
{
    // Input handler
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    bool hug_wall = hug_wall_left || hug_wall_right;

    // ===============Main input===============

    // Moving L/R
    if (can_move && !g_dash && !a_dash && !crawl)
    {
        if (state[SDL_SCANCODE_A] && !hug_wall_right)
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

        if (state[SDL_SCANCODE_D] && !hug_wall_left)
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
    crawl = can_crawl && state[SDL_SCANCODE_S] && on_ground && !g_dash && !decel_x && !g_dash_delay && abs(vel_x) < vel_x_max / 2;
    crawl = crawl_lock || crawl;

    if (crawl && state[SDL_SCANCODE_A] && !g_dash)
        vel_x = -vel_crawl;
    if (crawl && state[SDL_SCANCODE_D] && !g_dash)
        vel_x = vel_crawl;

    // Deceleration
    if ((!state[SDL_SCANCODE_A] && decel_x == 1) ||
        (!state[SDL_SCANCODE_D] && decel_x == -1))
        decel_x = 0;

    if (!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D] && !g_dash && !a_dash)
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
    if (can_g_dash && state[SDL_SCANCODE_LSHIFT] && !g_dash_delay && !combat_index && on_ground && !g_dash && !crawl_lock && !a_dash)
    {
        g_dash = true;
        g_dash_delay = g_dash_delay_max * (crawl ? 1.5 : 1);

        if (weapon_equip)
        {
            combat_hit_up = 20;
            combat_hit_down = 20;
            if (act_right) combat_hit_right = 80;
            else combat_hit_left = 80;

            combat_damage = crawl ? 20 : 12;
        }
    }

    // Air dash
    if (can_a_dash && state[SDL_SCANCODE_LSHIFT] && !a_dash_delay && !combat_index && !on_ground && !hug_wall && !crawl && !g_dash && vel_x != 0 && air_cur > 0 && !jump_keyhold)
    {
        a_dash = true;
        air_cur--;
        a_dash_delay = a_dash_delay_max;

        if (weapon_equip)
        {
            combat_hit_up = 30;
            combat_hit_down = 30;
            combat_damage = 10;
            if (act_right) combat_hit_right = 80;
            else combat_hit_left = 80;
        }
    }

    // Jump held key
    if (can_jump && state[SDL_SCANCODE_SPACE] && !jump_keyhold && (air_cur > 0 || hug_wall) &&
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
    if (!state[SDL_SCANCODE_SPACE])
    {
        jump_keyhold = false;
    }

    // ===================== COMBAT (EXTREMELY EPIC) ====================

    // Weapom equipment
    if (state[SDL_SCANCODE_E] && (!weapon_equip_delay || weapon_equip) && !weapon_equip_keyhold &&
        on_ground && vel_x == 0)
    {
        weapon_equip_delay = weapon_equip_delay_max;
        weapon_equip_keyhold = true;
        weapon_equip = weapon_equip ? false : true;
    };
    if (!state[SDL_SCANCODE_E]) weapon_equip_keyhold = false;

    if (!weapon_equip) return;

    // Attack pattern (really fucking sophisicated)

    if (state[SDL_SCANCODE_L])
    {
        combat_keytime++;
        combat_keyhold = !combat_keytap && combat_keytime > 20;
    }

    if (!state[SDL_SCANCODE_L])
    {
        combat_keytap = combat_keytime <= 20 && combat_keytime > 0;
        combat_keyhold = false;
        combat_keytime = 0;
    }
}

void Player::playerMovement()
{   
    // Velcovity
    vel_x_max = on_ground ? vel_x_max_ground : vel_x_max_air;
    vel_x_max *= weapon_equip ? .8 : 1;
    // Acelecreaitm
    accel_x = on_ice ? accel_x_ice : accel_x_ground;
    accel_x *= weapon_equip ? .8 : 1;
    accel_y = jump_keyhold ? accel_hold : accel_tap;
    accel_y *= weapon_equip ? 1.2 : 1;
    // G_dash
    g_dash_vel = weapon_equip ? g_dash_vel_weapon : g_dash_vel_normal;
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

        vel_x = (1 + 90 / (air_max - air_cur + 6)) * (vel_x > 0 ? 1 : -1);
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

    // On groudn
    if (!on_ground && air_cur == air_max)
        air_cur = air_max - 1;
    if (on_ground)
        air_cur = air_max;

    setY(getY() + vel_y);
}

void Player::playerCombat()
{
// ===================== COMBAT (VERY LEGENDARY) ====================

    if (invincible_time) {
        if (invincible_time > invincible_time_max * .8)
        {
            vel_x = 0;
            vel_y = 0;
        }
        invincible_time--;
        SDL_SetTextureAlphaMod(playerCurrentTexture, (invincible_time % 15 > 0) ? 200 : 160);
    }

    // Weapon draw delay
    if (weapon_equip_delay > 0)
        weapon_equip_delay--;

    if (combat_time)
        combat_time--;
    
    if (combat_combo_time)
        combat_combo_time--;
    else
        combat_index = 0;

    if (combat_delay)
    {
        combat_delay--;
        // if (!combat_delay)
        //     Audio::playSFX("res/Audio/SFX/CombatReady.wav");
    }

    // =================== Combat hitbox handler ===================
    if (!combat_time && !a_dash && !g_dash)
    {
        combat_hit_up = 0;
        combat_hit_down = 0;
        combat_hit_right = 0;
        combat_hit_left = 0;
        combat_damage = 0;
    }

    if (combat_index == 1)
    {
        combat_hit_up = 40;
        combat_hit_down = 40;
        combat_hit_right = act_right ? 100 : 0;
        combat_hit_left = act_right ? 0 : 100;
        combat_damage = 10;
    }

    if (combat_index == 2)
    {
        combat_hit_up = 15;
        combat_hit_down = 15;
        combat_hit_right = act_right ? 120 : 0;
        combat_hit_left = act_right ? 0 : 120;
        combat_damage = 20;
    }

    if (combat_index == 3)
    {
        combat_hit_up = 80;
        combat_hit_down = 60;
        combat_hit_right = act_right ? 100 : 0;
        combat_hit_left = act_right ? 0 : 100;
        combat_damage = 30;
    }

    // =================== Combat Attack Pattern ===================
    bool hug_wall = hug_wall_left || hug_wall_right;

    // On ground
    if (!combat_delay && combat_keytap && !hug_wall && !crawl && !g_dash && on_ground)
        if (!combat_combo_time && !combat_index)
        {
            combat_index = 1;
            combat_time = 15;
            combat_combo_time = 40;
            setEndLock(false);
        }
        else if (!combat_time && combat_index == 1 && combat_combo_time)
        {
            combat_index = 2;
            combat_time = 15;
            combat_combo_time = 35;
            setEndLock(false);
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

    if (!combat_delay && combat_keyhold && !crawl && !vel_x)
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
                playerGetHit(enemy->getCollideDamage());

            // Addition enemy logic
            enemy->enemyPlayerCollision(this);
        }


    // ================== DEALING DAMAGE =======================
        if (!(enemy->getInvinTime()) &&
            (combat_time || a_dash || g_dash))
        {
            if ((enemy->getX() > getHitX()? colli_x < combat_hit_right + enemy->getHitWidth() / 2 :
                                            colli_x < combat_hit_left  + enemy->getHitWidth() / 2) &&
                (enemy->getY() > getHitY()? colli_y < combat_hit_up    + enemy->getHitHeight() / 2 :
                                            colli_y < combat_hit_down  + enemy->getHitHeight() / 2))
            {
                Audio::playSFX("res/Audio/SFX/Bonk.wav");
                enemy->enemyGetHit(combat_damage);

                if (a_dash || g_dash) vel_x = -vel_x;
            }
        }
    }
}

void Player::playerGetHit(int dmg)
{
    if (invincible_time) return;
    invincible_time = invincible_time_max;
    hp -= dmg;
}

void Player::playerDeveloper()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    int vel_developer = state[SDL_SCANCODE_LSHIFT] ? 20 : 4;
    if (state[SDL_SCANCODE_W]) setY(getY() + vel_developer);
    if (state[SDL_SCANCODE_S]) setY(getY() - vel_developer);
    if (state[SDL_SCANCODE_D]) setX(getX() + vel_developer);
    if (state[SDL_SCANCODE_A]) setX(getX() - vel_developer);
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
        playerInput();
        playerMovement();
        playerCombat();
        playerBlockCollision(map->BlockVec);
        playerEnemyCollision(map->EnemyVec);
    }
    else
    {
        playerDeveloper();
    }
    // playerEventTrigger(event);

    playerSpriteIndex();

    // ===============DEVELOPER input===============
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    // GODMODE
    if (state[SDL_SCANCODE_H] && !godmode_hold)
    {
        godmode_hold = true;
        godmode = godmode ? false : true;
    }
    if (!state[SDL_SCANCODE_H]) godmode_hold = false;

    // DISPLAY GRID
    if (state[SDL_SCANCODE_G] && !grid_hold)
    {
        grid_hold = true;
        grid = grid ? false : true;
    };
    if (!state[SDL_SCANCODE_G]) grid_hold = false;
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