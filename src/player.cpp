#include "player.h"

// Constructor
Player::Player(float X, float Y, int w, int h, int hw, int hh, int sim, int sfm, int si, int sf) : Object2D(X, Y, w, h, hw, hh, sim, sfm, si, sf) {}

// Fuck her 2nite
void Player::initPlayer(SDL_Renderer *renderer)
{
    // Nakuru facing right sprite
    PlayerRight = new Sprite(32, 32, 4, "res/NakuSheet/NakuRight.png");
    PlayerRight->setTexture(Sprite::loadTexture(renderer, PlayerRight->getSpritePath()));

    // Nakuru facing left sprite
    PlayerLeft = new Sprite(32, 32, 4, "res/NakuSheet/NakuLeft.png");
    PlayerLeft->setTexture(Sprite::loadTexture(renderer, PlayerLeft->getSpritePath()));

    hitbox = new Sprite(100, 100, 1, "res/HitboxMyass.png");
    hitbox->setTexture(Sprite::loadTexture(renderer, hitbox->getSpritePath()));

    setFocusXCondition([](int x, int y)
                       {
        if (x > Game::WIDTH / 2) FocusReturn(Game::WIDTH / 2, true);
        FocusReturn(0, false); });
    setFocusYCondition([](int x, int y)
                       {
        if (y > Game::HEIGHT / 2) FocusReturn(Game::HEIGHT / 2, true);
        FocusReturn(0, false); });

    // Testing out the invinsibility and stuff
    setSpriteAlpha(255);
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
        SDL_SetTextureAlphaMod(PlayerLeft->getTexture(), alpha);
        SDL_SetTextureAlphaMod(PlayerRight->getTexture(), alpha);
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

// Getter
float Player::getVelX()
{
    return vel_x;
}
float Player::getVelY()
{
    return vel_y;
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

// Things for hud
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

// Other Method

void Player::playerSprite(SDL_Renderer *renderer)
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
    int drawY = focus_y ? Game::HEIGHT / 2 : Game::HEIGHT - getY();

    if (display_hitbox)
    {
        int drawHitX = focus_x ? Game::WIDTH / 2 - hit_offset_x : getHitX();
        int drawHitY = focus_y ? Game::HEIGHT / 2 - hit_offset_y : Game::HEIGHT - getHitY();
        SDL_Rect hitRect = {drawHitX - getHitWidth() / 2, drawHitY - getHitHeight() / 2, getHitWidth(), getHitHeight()};
        SDL_RenderCopy(renderer, hitbox->getTexture(), NULL, &hitRect);
    }

    SDL_Rect desRect = {drawX - getWidth() / 2, drawY - getWidth() / 2, getWidth(), getHeight()};
    SDL_Rect srcRect = {getSprIndex() * 32, act_index * 32, 32, 32};
    SDL_RenderCopy(renderer, act_right ? PlayerRight->getTexture() : PlayerLeft->getTexture(), &srcRect, &desRect);
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
    // std::cout << crawl_lock << "\n";

    if (crawl && state[SDL_SCANCODE_A] && !g_dash)
    {
        vel_x = -vel_crawl;
    }
    if (crawl && state[SDL_SCANCODE_D] && !g_dash)
    {
        vel_x = vel_crawl;
    }

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
    if (can_g_dash && state[SDL_SCANCODE_LSHIFT] && on_ground && !g_dash && !crawl_lock && !a_dash && !g_dash_delay)
    {
        g_dash = true;
        g_dash_delay = g_dash_delay_max * (crawl ? 1.5 : 1);
        vel_x = g_dash_vel * (act_right ? 1 : -1) * (crawl ? 1.4 : 1);
    }

    // Air dash
    if (can_a_dash && state[SDL_SCANCODE_LSHIFT] && !a_dash_hold && !on_ground && !hug_wall && !crawl && !g_dash && vel_x != 0 && air_cur > 0 && !jump_hold)
    {
        a_dash_hold = true;
        air_cur--;

        a_dash = true;
        vel_x = (1 + 90 / (air_max - air_cur + 6)) * (vel_x > 0 ? 1 : -1);
    }
    if (!state[SDL_SCANCODE_LSHIFT])
        a_dash_hold = false;

    // Jump held key
    if (can_jump && state[SDL_SCANCODE_SPACE] && !jump_hold && (air_cur > 0 || hug_wall) && !g_dash && !a_dash && !decel_x && !crawl_lock && !ceiling_knockout)
    {
        setY(getY() + 10);
        on_ground = false;

        vel_y = 1 + 40 / (air_max - air_cur + 8);
        if (jump_super == jump_super_max)
            vel_y = 7;
        accel_y = accel_hold;

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

        jump_hold = true;
    }
    // Jump release key
    if (!state[SDL_SCANCODE_SPACE])
    {
        jump_hold = false;
        accel_y = accel_tap;
    }

    // ===============EXPERIMENTATION input===============
    display_hitbox = state[SDL_SCANCODE_H];
}

void Player::playerMovement()
{
    vel_x_max = on_ground ? vel_x_max_ground : vel_x_max_air;
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
    {
        vel_y = 0;
    }
    else if (hug_wall_left || hug_wall_right)
    {
        vel_y = -1;
    }
    else
    {
        vel_y -= accel_y;
    }
    // Terminal Velocity
    if (vel_y <= -vel_terminal)
    {
        vel_y = -vel_terminal;
    }
    // Air Dashing
    if (a_dash)
        vel_y = 0;

    // Ground Stuff
    if (crawl && vel_x == 0)
    {
        jump_super += jump_super < jump_super_max;
    }
    else
    {
        jump_super = 0;
    }

    if (g_dash)
    {
        g_dash_frame++;
        if (g_dash_frame >= g_dash_frame_max)
        {
            g_dash_frame = 0;
            g_dash = false;
        }
    }
    if (g_dash_delay > 0)
    {
        g_dash_delay--;
    }
    // a_Dashing
    if (a_dash)
    {
        a_dash_frame++;
        if (a_dash_frame >= a_dash_frame_max)
        {
            a_dash_frame = 0;
            a_dash = false;
        }
    }

    // Ceiling knock out
    if (ceiling_knockout > 0)
        ceiling_knockout--;

    if (on_ground)
    {
        air_cur = air_max;
    }

    setY(getY() + vel_y);

    if (getY() < 0)
    {
        setX(640);
        setY(200);
    }

    // std::cout << getY() << " " << vel_y << "\n";
    // std::cout << getY() << "\n";
}

void Player::playerAction()
{
    act_right = vel_x > .2 ? 1 : vel_x < -.2 ? 0
                                             : act_right;
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
        setSprite(8, 30 - abs(vel_x) * 5);
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
        setSprite(4, 5);
    }
    // Air Dashing
    if (a_dash)
    {
        setEndLock(true);
        setAct(5, act_right);
        setSprite(4, 10);
    }
    // Not ground nor air dashing
    if (!a_dash && !g_dash)
    {
        setEndLock(false);
    }

    // Crawl
    if (crawl)
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

void Player::playerTileCollision(std::vector<Block *> BlockVec)
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

    for (Block *obj : BlockVec)
    {
        // ==Distance with each other==
        // I don't wanna only call your name when I'm brokenhearted (yeah)
        // I already know how much you've got to lose (oh-oh, oh-oh)
        // I don't wanna have to crash and burn to be where we started (yeah)
        // I don't wanna ever need a map to you (oh)
        // I've run so far and so high
        // I'll chase the sun 'til light time
        // But I ain't gonna keep my distance from you
        // Yeah, I already know what distance can do
        // If I let you get away, bury me today
        // Yeah, I ain't gonna keep my distance from you (oh, yeah)
        // I'm so good at walls, good at lies
        // Putting up my fences (oh, yeah)
        // I'm human as it gets when it comes to you (oh, yeah)
        // Looking in the mirror, seeing a man with a million faces (oh, no)
        // But every single one, they know the truth
        // But I ain't gonna keep my distance from you
        // Yeah, I already know what distance can do
        // If I let you get away, bury me today
        // Yeah, I ain't gonna keep my distance from you
        // I've run so far and so high
        // I'll chase the sun 'til light time
        // But I ain't gonna keep my distance from you
        // Yeah, I already know what distance can do
        // If I let you get away, bury me today
        // Yeah, I ain't gonna keep my distance from you (oh, yeah)
        int hit_dist_x = (getHitWidth() + obj->getHitWidth()) / 2;
        int hit_dist_y = (getHitHeight() + obj->getHitHeight()) / 2;
        int hit_dist_y_stand = (80 + obj->getHitHeight()) / 2;

        int colli_x = abs(getHitX() - obj->getX());
        int colli_y = abs(getHitY() - obj->getY());
        int colli_y_stand = abs(getY() - obj->getY());

        // Hit Left wall
        if (getHitX() < obj->getX() && colli_x < hit_dist_x &&
            getHitY() < obj->getY() + hit_dist_y - 10 &&
            getHitY() > obj->getY() - hit_dist_y + 10)
        {
            if (can_hug_wall && !on_ground && !a_dash)
            {
                hug_aleast_wall = true;
                hug_wall_left = true;
                vel_x = 0;
                setX(obj->getX() - hit_dist_x + 3);
            }
            else
            {
                setX(obj->getX() - hit_dist_x);
                if (a_dash || g_dash)
                    vel_x = -vel_x * .5;
                act_right = 1;
            }

            continue;
        }

        // Hit Right wall
        if (getHitX() > obj->getX() && colli_x < hit_dist_x &&
            getHitY() < obj->getY() + hit_dist_y - 10 &&
            getHitY() > obj->getY() - hit_dist_y + 10)
        {
            if (can_hug_wall && !on_ground && !a_dash)
            {
                setX(obj->getX() + hit_dist_x - 3);
                hug_aleast_wall = true;
                hug_wall_right = true;
                vel_x = 0;
            }
            else
            {
                setX(obj->getX() + hit_dist_x);
                if (a_dash || g_dash)
                    vel_x = -vel_x * .5;
                act_right = 0;
            }

            continue;
        }

        // Ceiling logic
        if ((getHitX() < obj->getX() + hit_dist_x) &&
            (getHitX() > obj->getX() - hit_dist_x))
        {
            if (vel_y > 0 && getHitY() < obj->getY() &&
                colli_y < hit_dist_y - vel_y)
            {
                ceiling_knockout = ceiling_knockout_delay;
                setY(obj->getY() - obj->getHeight() / 2 - 40 - vel_y);
                vel_y = -vel_y * 0.1;
                continue;
            }

            if (on_ground && getY() < obj->getY() &&
                colli_y_stand < hit_dist_y_stand)
            {
                crawl_lock_atleast = true;
            }
        }

        // Stand on block
        if (!on_aleast_ground &&
            getHitY() > obj->getY() &&
            colli_y < hit_dist_y &&
            (getHitX() < obj->getX() + hit_dist_x) &&
            (getHitX() > obj->getX() - hit_dist_x))
        {
            if (obj->getMoving())
            {
                setX(getX() + obj->getVelX());
                setY(getY() + obj->getVelY());
            }
            
            // vel_y = 0;
            
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
    };
}

// void Player::playerEventTrigger(EventTrigger *event[])
// {
//     for (int i = 0; i < 1; i++)
//     {
//         EventTrigger *eve = event[i];
//         int colli_x = abs(getX() - eve->getX());
//         int colli_y = abs(getY() - eve->getY());
//         int hit_dist_x = (getHitWidth() + eve->getHitWidth()) / 2;
//         int hit_dist_y = (getHitHeight() + eve->getHitHeight()) / 2;

//         if (colli_x < hit_dist_x && colli_y < hit_dist_y)
//         {
//             eve->triggerEvent(1);
//         }
//     }
// }

void Player::playerUpdate(SDL_Renderer *renderer, std::vector<Block *> BlockVec)
{
    playerInput();
    playerMovement();
    playerTileCollision(BlockVec);
    // playerEventTrigger(event);

    playerAction();
    playerSprite(renderer);
}