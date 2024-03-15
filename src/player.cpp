#include "player.h"

// Constructor
Player::Player(float X, float Y, int w, int h, int hw, int hh, int sim, int sfm, int si, int sf) : 
    Object2D(X, Y, w, h, hw, hh, sim, sfm, si, sf) {}

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

    setFocusXCondition([](int x, int y) {
        if (x > 640) FocusReturn(640, true);
        FocusReturn(0, false);
    });
    setFocusYCondition([](int x, int y) {
        if (y > 360) FocusReturn(360, true);
        FocusReturn(0, false);
    });

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
        act_right = right || false;
    }
}

void Player::setSprite(int m_index, int m_frame)
{
    setSprFrameMax(m_frame);
    setSprIndexMax(m_index);
}

void Player::setSpriteAlpha(int alpha)
{
    if (sprite_alpha != alpha) {
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
int Player::getGridX()
{
    return getX() / getWidth();
}
int Player::getGridY()
{
    return getY() / getHeight();
}
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

    setFocus();

    int drawX = focus_x ? 640 : getHitX();
    int drawY = focus_y ? 360 : 720 - getHitY();
    SDL_Rect desRect = {drawX - getWidth() / 2, drawY - getWidth() / 2, getWidth(), getHeight()};
    SDL_Rect srcRect = {getSprIndex() * 32, act_index * 32, 32, 32};


    SDL_Rect hitRect = {drawX - getHitWidth() / 2, drawY - getHitHeight() / 2, getHitWidth(), getHitHeight()};

    SDL_RenderCopy(renderer, hitbox->getTexture(), NULL, &hitRect);
    SDL_RenderCopy(renderer, act_right ? PlayerRight->getTexture() : PlayerLeft->getTexture(), &srcRect, &desRect);
}

void Player::playerInput()
{
    // Input handler
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    // ===============Working===============

    // Moving L/R
    if (state[SDL_SCANCODE_A] && !g_dash && !a_dash && !crawl)
    {
        if (vel_x > .6)
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
    if (state[SDL_SCANCODE_D] && !g_dash && !a_dash && !crawl)
    {
        if (vel_x < -.6)
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

    // Crawling
    crawl = state[SDL_SCANCODE_S] && !g_dash && on_ground;

    if (crawl && state[SDL_SCANCODE_A]) {
        vel_x = -vel_crawl;
    }
    if (crawl && state[SDL_SCANCODE_D]) {
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
    if (state[SDL_SCANCODE_LSHIFT] && on_ground && !crawl && !g_dash && !a_dash && vel_x != 0)
    {
        g_dash = true;
        vel_x = g_dash_vel * (vel_x > 0 ? 1 : -1);
    }

    // Jump held key
    if (state[SDL_SCANCODE_SPACE] && decel_x == 0 && air_cur > 0 && !jump_hold && !g_dash && !a_dash && !crawl)
    {
        setY(getY() + 10);
        on_ground = false;

        air_cur--;
        vel_y = 1 + 24 / (air_max - air_cur + 8);


        jump_hold = true;
    }
    // Jump release key
    if (!state[SDL_SCANCODE_SPACE])
    {
        jump_hold = false;
    }

    // Air dash
    if (state[SDL_SCANCODE_LSHIFT] && !on_ground && !crawl && !g_dash &&
        !a_dash && vel_x != 0 && air_cur > 0 && !jump_hold)
    {
        air_cur--;

        a_dash = true;
        vel_x = a_dash_vel * (vel_x > 0 ? 1 : -1);
    }
}

void Player::playerMovement()
{
    setHitWidth(58);
    setHitHeight(78);

    // Cap X velocity
    if (!g_dash && !a_dash) {
        if (vel_x < -vel_x_max)
            vel_x = -vel_x_max;
        if (vel_x > vel_x_max)
            vel_x = vel_x_max;
    }
    setX(getX() + vel_x);

    // Vertigo is a bad map
    if (on_ground) {
        vel_y = 0;
    } else {
        vel_y -= (accel_y / 1.2);
    }
    // Terminal Velocity
    if (vel_y <= -vel_terminal) {
        vel_y = -vel_terminal;
    }
    // Dashing
    if (a_dash) vel_y = 0;
    
    // std::cout << getY() << " " << vel_y << "\n";
    // std::cout << vel_y << "\n";

    if (on_ground) {
        air_cur = air_max;
    }

    // g_Dashing
    if (g_dash)
    {
        g_dash_frame++;
        if (g_dash_frame >= g_dash_frame_max)
        {
            g_dash_frame = 0;
            g_dash = false;
        }
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

    setY(getY() + vel_y);

    if (getY() < 0) SDL_Quit();
}

void Player::playerAction()
{
    if (abs(vel_x) <= .2)
    {
        // Idling
        setAct(0, act_right);
        setSprite(2, 100);
    }
    else
    {
        // Moving
        setAct(1, vel_x > 0);
        setSprite(8, 50 - abs(vel_x) * 16);
    }

    // Decelerating
    if (decel_x != 0)
    {
        setAct(2, decel_x > 0);
        setSprite(2, 4);
    }

    // Jumping
    if (vel_y > .2 && !on_ground)
    {
        setAct(3, act_right);
        setSprite(4, 25);
    }
    if (vel_y < .2 && !on_ground)
    {
        setAct(3, act_right);
        setSprite(8, 5);
    }

    // Ground Dashing
    if (g_dash)
    {
        setEndLock(true);
        setAct(4, act_right);
        setSprite(4, 18);
    }
    // Air Dashing
    if (a_dash)
    {
        setEndLock(true);
        setAct(5, act_right);
        setSprite(4, 20);
    }
    // Not ground nor air dashing
    if (!a_dash && !g_dash)
    {
        setEndLock(false);
    }

    // Crawl
    if (crawl) {
        setAct(6, act_right);

        setSprite((abs(vel_x) > 0 ? 4 : 1), 10);
    }
}

void Player::playerTileCollision(Block *object[])
{
    bool on_aleast_ground = false;

    for (int i = 0; i < 3; i++)
    {
        Block *obj = object[i];
        // int colli_x = abs(getX() - obj->getX());
        int colli_y = abs(getY() - obj->getY());

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

        // Stand on block
        if (getY() > obj->getY() && colli_y < hit_dist_y &&
        (getX() < obj->getX() + hit_dist_x) &&
        (getX() > obj->getX() - hit_dist_x)) {
            on_ground = true;
            on_aleast_ground = true;
            break;
        }
        // Hit ceiling
        if (getY() < obj->getY() && colli_y < hit_dist_y &&
        (getX() < obj->getX() + hit_dist_x) &&
        (getX() > obj->getX() - hit_dist_x)) {
            setY(obj->getY() - obj->getHeight());
            vel_y = -vel_y * .2;
            break;
        }

        // if (getX())
    }

    if (!on_aleast_ground) on_ground = 0;
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

void Player::playerUpdate(SDL_Renderer *renderer, Block *object[])
{
    playerInput();
    playerTileCollision(object);
    // playerEventTrigger(event);
    playerMovement();
    playerAction();
    playerSprite(renderer);
}