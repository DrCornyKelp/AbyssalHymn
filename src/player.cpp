#include <map.h>

// Destructor
Player::~Player()
{ draw_prop.clearTexture(); }
// Constructor
Player::Player(bool mc) : Object2D(), MAIN(mc)
{
    // Nakuru normal mvoement
    draw_prop.RightTexture = loadTexture("res/NakuSheet/NakuRight.png");
    draw_prop.LeftTexture = loadTexture("res/NakuSheet/NakuLeft.png");

    // Nakuru holding weapon
    draw_prop.RightWeaponTexture = loadTexture("res/NakuSheet/NakuRightWeapon.png");
    draw_prop.LeftWeaponTexture = loadTexture("res/NakuSheet/NakuLeftWeapon.png");

    draw_prop.RightFriction = new ParticleEffect(
        loadTexture("res/ParticleSheet/NakuEffect/SlideFrictionRight.png"),
        0, 0, 70, 64, 54, 53, 5, 1, true
    );
    draw_prop.LeftFriction = new ParticleEffect(
        loadTexture("res/ParticleSheet/NakuEffect/SlideFrictionLeft.png"),
        0, 0, 70, 64, 54, 53, 5, 1, true
    );
}

// ============================ PLAYER STATE ============================

void PlayerState::resetState()
{
    on_ground = 0;
    on_ice = 0;
    in_water = 0;
    hug_wall = 0;
    crawl_lock = 0;
}

// ============================ PLAYER MOVING ============================

int PlayerMoving::hitX()
{ return player->getX() + hit_offset_x; }
int PlayerMoving::hitY()
{ return player->getY() + hit_offset_y; }

// ============================ PLAYER DRAW PROP ============================

void PlayerDrawProp::clearTexture()
{
    Object2D::deleteTextures({
        CurrentTexture,
        RightTexture, LeftTexture,
        RightWeaponTexture, LeftWeaponTexture
    });
    delete RightFriction, LeftFriction;
}

void PlayerDrawProp::setAct(int idx, bool r)
{
    if (index != idx || right != r)
    { index = idx; right = r; }
}

void PlayerDrawProp::setSprite(int m_index, int m_frame)
{
    player->setSprFrameMax(m_frame);
    player->setSprIndexMax(m_index);
}

void PlayerDrawProp::setSpriteAlpha(int alp)
{
    if (alpha != alp)
    {
        alpha = alp;
        SDL_SetTextureAlphaMod(CurrentTexture, alpha);
    }
}

void PlayerDrawProp::setEndLock(bool lock)
{
    if (lock && !end_lock)
    {
        player->setSprFrame(0);
        player->setSprIndex(0);
    }
    end_lock = lock;
}

void PlayerDrawProp::setActSprElock(int1D act, int1D spr, short lock)
{
    setAct(act[0], act[1]);
    setSprite(spr[0], spr[1]);
    // Lock: -1: no lock, 0: ignore, 1: lock
    if (lock) setEndLock(lock > 0);
}

void PlayerDrawProp::playerDrawProperty(Map *map)
{
    // ======================== SRPITES ===========================
    // Set index and stuff
    right = player->getVelX() > .2 ? 1 :
            player->getVelX() < -.2 ? 0 : right;

    // Ow< ouch
    // if (combat.invulnerable > combat.invulnerable_tim * .8)
    // { setActSprElock({8, right}, {1, 0}); return; }

    // Movement
    if (!player->combat.index)
    {
        // Idling
        if (abs(player->getVelX()) <= .2)
            setActSprElock({0, right}, {2, 64});
        // Moving
        else
            setActSprElock(
                {1, right},
                {8, 30 - int(abs(player->getVelX()) * 4)}
            );
        // Decelerating
        if (player->move.decel != 0)
            setActSprElock({2, player->move.decel > 0}, {2, 2});
        // Jumping
        if (!player->jump.coyote && !player->state.on_ground)
            setActSprElock({3, right}, {
                (player->getVelY() > .2 ? 4 : 8),
                (player->getVelY() > .2 ? 16 : 8)
            });
        // Ground Dashing
        if (player->g_dash.frame)
            setActSprElock({4, right}, {8, 3}, 1);
        // Air Dashing
        if (player->a_dash.frame)
            setActSprElock({5, right}, {4, 10}, 1);
        // Crawl
        if (player->move.crawl &&
            !(player->g_dash.frame && player->state.crawl_lock))
            setActSprElock({6, right}, {
                (abs(player->getVelX()) > 0 ? 4 : 1), 8
            });
        // Wall Sliding
        if (player->state.hug_wall)
            setActSprElock({7, player->state.hug_wall > 0}, {4, 8});
    }
    else
    {
        // ============= COMBAT SPRITE =============

        switch (player->combat.index)
        {
        case 1:
            if (!player->combat.time) break;
            setActSprElock({10, right}, {8, 2}, 1);
            break;
        
        case 2:
            if (!player->combat.time) break;
            setActSprElock({11, right}, {8, 2}, 1);
            break;

        case 3:
            switch (map->MapInput->getKeyHold(6))
            {
            case 0:
                setActSprElock({13, right}, {4, 2}, 1);
                break;

            case 1:
                setActSprElock({12, right}, {
                    player->getVelX() ? 4 : 1,
                    30 - int(abs(player->getVelX()) * 4)
                });
                break;
            }
            break;

        case 4:
            if (!player->combat.time) break;
            setActSprElock({14, right}, {8, 2}, 1);
            break;

        case 5:
            if (!player->combat.time) break;
            setActSprElock({15, right}, {8, 1}, 1);
            break;

        default:
            break;
        }
    }

    // Weapon draw
    if (player->combat.weapon_equip_frame)
    {
        if (player->combat.weapon_equip)
            setActSprElock({9, right}, {8, 3});
        setEndLock(false);
    }

    if (!player->g_dash.frame && !player->a_dash.frame &&
        !player->combat.weapon_equip_delay && !player->combat.index)
        setEndLock(false);

    // ============= SET SPRITE ==============

    CurrentTexture = right ?
        (player->combat.weapon_equip ? RightWeaponTexture : RightTexture) :
        (player->combat.weapon_equip ? LeftWeaponTexture : LeftTexture);

    player->setWidth(player->combat.weapon_equip ? 64 : 32);
}

void PlayerDrawProp::playerDrawSprite()
{
    player->objectSetSprite(end_lock);

    if (!player->combat.invulnerable)
        SDL_SetTextureAlphaMod(CurrentTexture, 255);

    if (player->g_dash.frame && player->state.on_ground)
    {
        if (player->getVelX() < 0)
        {
            LeftFriction->setX(player->getX() + 50);
            LeftFriction->setY(player->getY() - 8);
            LeftFriction->draw(player);
        }
        else
        {
            RightFriction->setX(player->getX() - 50);
            RightFriction->setY(player->getY() - 8);
            RightFriction->draw(player);
        }
    }
    SDL_Rect desRect;
    if (player->MAIN) desRect = {
        Camera::playerDrawX(player, player->getWidth()*4),
        Camera::playerDrawY(player, player->getWidth()*4),
        player->getWidth()*4, player->getWidth()*4
    };
    else desRect = {
        Camera::objectDrawX(player->MULTI->MAIN, player) - player->getWidth(),
        Camera::objectDrawY(player->MULTI->MAIN, player) - player->getWidth()*2,
        player->getWidth()*4, player->getWidth()*4
    };

    SDL_Rect srcRect = {
        player->getSprIndex() * player->getWidth(),
        index * player->getWidth(),
        player->getWidth(), player->getWidth()
    };

    SDL_RenderCopy(CFG->RENDERER, CurrentTexture, &srcRect, &desRect);
}

// Combat / Hitbox
// int Player::getHitX() { return getX() + hit_offset_x; }
// int Player::getHitY() { return getY() + hit_offset_y; }

// ============================ PLAYER CAMERA ============================

void PlayerCamera::resetCamera()
{
    ease_x = 0; ease_y = 0;
    effect_x = 0; effect_y = 0;
    offset_mid_x = 0; offset_mid_y = 0;
}

void PlayerCamera::setCameraBorder(ObjectBox f_dir, ObjectBox f_val)
{
    focus_dir = f_dir;

    // Get The Border
    focus_border = f_val;
    // Weird reasoning too lazy to explain
    focus_border.up += 1;
    focus_border.right += 1;
    // Grid 64
    focus_border.grid(64);

    // Get The Point
    focus_point = focus_border;
    focus_point.up -= CFG->HEIGHT / 2;
    focus_point.down += CFG->HEIGHT / 2;
    focus_point.left += CFG->WIDTH / 2;
    focus_point.right -= CFG->WIDTH / 2;

    // Too Small of a Box -> Centering
    if (focus_dir.up && focus_dir.down &&
        focus_point.up <= focus_point.down)
    {
        focus_point.up += (focus_point.down - focus_point.up) / 2;
        focus_point.down = focus_point.up;
    }
    if (focus_dir.left && focus_dir.right &&
        focus_point.right <= focus_point.left)
    {
        focus_point.right += (focus_point.left - focus_point.right) / 2;
        focus_point.left = focus_point.right;
    }

    focus_border.reorder();
}

// Still a WIP (more like so useless i straight up dont care lmao)
void PlayerCamera::setCameraFocus(ObjectBox f_dir, ObjectBox f_val, short gr)
{ focus_dir = f_dir; focus_point = f_val; focus_point.grid(gr); }

// Camera Focus Trigger
int PlayerCamera::getFocusTriggerX() {
    return player->getX() - Camera::playerShiftX(player);
}
int PlayerCamera::getFocusTriggerY() {
    return player->getY() - Camera::playerShiftY(player);
}

// Stop Player Current State
void Player::setStatic()
{
    setVelX(0); setVelY(0);
    setSprFrame(0); setSprIndex(0);
    // Reset Movement
    move.crawl = 0;
    a_dash.frame = 0;
    g_dash.frame = 0;

    setHitWidth(58);
    setHitHeight(80);

    // Reset Combat
    combat.delay = 0;
    combat.combo_time = 0;
    combat.charge_time = 0;
}

void PlayerCamera::playerCameraFocus()
{
    int p_shift_x = Camera::playerShiftX(player);
    int p_shift_y = Camera::playerShiftY(player);

    // Readjust to goal value
    if (focus_true.up != focus_point.up)
        focus_true.up -= (focus_true.up - focus_point.up) / focus_speed;
    if (focus_true.down != focus_point.down)
        focus_true.down -= (focus_true.down - focus_point.down) / focus_speed;
    if (focus_true.left != focus_point.left)
        focus_true.left -= (focus_true.left - focus_point.left) / focus_speed;
    if (focus_true.right != focus_point.right)
        focus_true.right -= (focus_true.right - focus_point.right) / focus_speed;

    if (abs(focus_true.up - focus_point.up) <= focus_speed)
        focus_true.up = focus_point.up;
    if (abs(focus_true.down - focus_point.down) <= focus_speed)
        focus_true.down = focus_point.down;
    if (abs(focus_true.left - focus_point.left) <= focus_speed)
        focus_true.left = focus_point.left;
    if (abs(focus_true.right - focus_point.right) <= focus_speed)
        focus_true.right = focus_point.right;

    if (focus_snap && !focus_true.compare(focus_point))
    { focus_snap = 0;  focus_true.copy(focus_point); }

    // === Focus X ===

    // Boundary left
    if (focus_dir.left &&
        getFocusTriggerX() < focus_true.left)
    {
        unfocus_x = 1;
        unfocus_offset_x = focus_true.left + p_shift_x;
        offset_mid_x = player->getX() - focus_true.left - p_shift_x;
    }
    // Boundary right
    else if (focus_dir.right &&
        getFocusTriggerX() > focus_true.right)
    {
        unfocus_x = 1;
        unfocus_offset_x = focus_true.right + p_shift_x;
        offset_mid_x = player->getX() - focus_true.right - p_shift_x;
    }
    else
    {
        unfocus_x = 0;
        offset_mid_x = 0;
    }

    // === Focus Y ===

    // Boundary Down
    if (focus_dir.down &&
        getFocusTriggerY() < focus_true.down)
    {
        unfocus_y = 1;
        unfocus_direction_y = -1;
        unfocus_offset_y = focus_true.down + p_shift_y;
        offset_mid_y = player->getY() - focus_true.down - p_shift_y;
    }
    // Boundary Up
    else if (focus_dir.up &&
        getFocusTriggerY() > focus_true.up)
    {
        unfocus_y = 1;
        unfocus_direction_y = 1;
        unfocus_offset_y = focus_true.up + p_shift_y;
        offset_mid_y = player->getY() - focus_true.up - p_shift_y;
    }
    else
    {
        unfocus_y = 0;
        offset_mid_y = 0;
    }
}

void PlayerCamera::playerCameraProperty(Input *input)
{
    // ======================== CAMERA ============================
    
    // Center The camera in the middle if godmode
    if (player->getGodmode())
    {
        unfocus_x = 0;
        unfocus_y = 0;
        resetCamera();
        return;
    }
    else playerCameraFocus();

    // Look vertical up and down
    float vt_max = vertical_ahead_max;
    if (player->state.on_ground && !player->getVelX() &&
        vertical_ahead_time > vertical_ahead_time_max)
    {
        if (input->getKeyHold(0) &&
            vertical_ahead < vt_max &&
            !(  unfocus_direction_y == 1 &&
                player->getY() > unfocus_offset_y - vt_max))
            vertical_ahead += (vt_max - abs(vertical_ahead)) / 30;
        if (input->getKeyHold(1) &&
            vertical_ahead > -vt_max &&
            !(  unfocus_direction_y == -1 &&
                player->getY() < unfocus_offset_y + vt_max))
            vertical_ahead -= (vt_max - abs(vertical_ahead)) / 30;

        vertical_ahead = vertical_ahead > vt_max ? vt_max : vertical_ahead;
        vertical_ahead = vertical_ahead < -vt_max ? -vt_max : vertical_ahead;
    }

    if (player->state.on_ground && !player->getVelX() && !unfocus_y &&
        (input->getKeyHold(0) || input->getKeyHold(1)))
        vertical_ahead_time ++;
    else
        vertical_ahead_time = 0;

    if (player->getVelX() || player->getVelY() ||
        (!input->getKeyHold(0) && vertical_ahead > 0) ||
        (!input->getKeyHold(1) && vertical_ahead < 0))
        vertical_ahead -= vertical_ahead / 40;

    if (!unfocus_x)
    {
        float ease_x_max =  (player->combat.weapon_equip ? 64 : 96) +
                            // Velociy pass a cap
                            (player->getVelX()>player->move.vel_max ?
                                (player->getVelX()-player->move.vel_max)*64 : 0);
        // Damping / Easing effect X
        if (player->draw_prop.right && ease_x > -ease_x_max)
            ease_x -= abs(player->getVelX() / 5);
        if (!player->draw_prop.right && ease_x < ease_x_max)
            ease_x += abs(player->getVelX() / 5);
        // Turn off easing effect
        if (!player->getVelX() || abs(ease_x) > ease_x_max)
            ease_x -= ease_x / 100;

        // Dash Feel Faster
        if (player->g_dash.frame || player->a_dash.frame)
        {
            effect_x += player->getVelX() > 0 ? -2 : 2;
            effect_x = effect_x > 64 ? 64 : effect_x;
            effect_x = effect_x <-64 ?-64 : effect_x;
        }
        else if (effect_x)
            effect_x -= effect_x / 40;
    }
}

void Player::playerMovement(Map *map)
{
// ======================== Helpful values ==============================
    short dir = draw_prop.right ? 1 : -1;

// ======================== MOVEMENT INPUT ==============================
    // Moving L/R
    if (moveset.move && !g_dash.frame && !a_dash.frame && !move.crawl)
    {
        if (map->MapInput->getKeyHold(2) && state.hug_wall < 1)
        {
            // Release from wall
            if (state.hug_wall)
                setX(getX() - 4);
            state.hug_wall = 0;

            move.decel = getVelX() > 1;
            if (getVelX() - getAccelX() > -move.vel_max)
                setVelX(getVelX() - getAccelX() * (move.decel ? 2.5 : 1));
        }

        if (map->MapInput->getKeyHold(3) && state.hug_wall > -1)
        {
            if (state.hug_wall)
                setX(getX() + 4);
            state.hug_wall = 0;

            move.decel = getVelX() < -1;
            if (getVelX() + getAccelX() < move.vel_max)
                setVelX(getVelX() + getAccelX() * (move.decel ? 2.5 : 1));
        }
    }

    // Not moving anymore
    if (!map->MapInput->getKeyHold(2) &&
        !map->MapInput->getKeyHold(3) &&
        !g_dash.frame && !a_dash.frame)
    {
        if (abs(getVelX()) >= getAccelX())
            setVelX(getVelX() - getAccelX() * dir);
        else
            setVelX(0);
    }

    // No more deceleration
    if ((!map->MapInput->getKeyHold(2) && move.decel > 0) ||
        (!map->MapInput->getKeyHold(3) && move.decel < 0))
        move.decel = 0;

    // Crawling
    move.crawl= moveset.crawl && map->MapInput->getKeyHold(1) &&
                state.on_ground && !move.decel &&
                !g_dash.delay && !g_dash.frame &&
                abs(getVelX()) < move.vel_max / 2;
    move.crawl = state.crawl_lock || move.crawl;

    if (move.crawl && map->MapInput->getKeyHold(2) && !g_dash.frame)
        setVelX(-move.vel_crawl);
    if (move.crawl && map->MapInput->getKeyHold(3) && !g_dash.frame)
        setVelX(move.vel_crawl);

    // Ground dash (more like sliding but whatever)
    if (moveset.g_dash && map->MapInput->getKeyPress(5) && !g_dash.delay &&
        !state.crawl_lock && state.on_ground &&
        !g_dash.frame && !combat.index && !combat.weapon_equip_frame)
    {
        map->MapInput->setKeyHold(5, true);

        map->ParticleBackVec.push_back(new ParticleEffect(
            loadTexture(draw_prop.right ?
                "res/ParticleSheet/NakuEffect/GDashSmokeRight.png" :
                "res/ParticleSheet/NakuEffect/GDashSmokeLeft.png"
            ),
            getX(), getY(), 100, 71,
            59, 42, 7, 5, 0
        ));

        g_dash.frame = move.crawl ? 32 : 24;
        g_dash.delay = move.crawl ? 40 : 25;
    }

    // Air dash
    if (moveset.a_dash && map->MapInput->getKeyPress(5) &&
        !a_dash.frame && a_dash.cur &&
        !state.on_ground && !state.hug_wall &&
        !combat.index && !combat.weapon_equip_frame &&
        (   (getVelX() > 0 && a_dash.lock != 1) ||
            (getVelX() < 0 && a_dash.lock != -1) )
        )
    {
        map->MapInput->setKeyHold(5, true);

        map->ParticleBackVec.push_back(new ParticleEffect(
            loadTexture(draw_prop.right ?
                "res/ParticleSheet/NakuEffect/ADashSmokeRight.png" :
                "res/ParticleSheet/NakuEffect/ADashSmokeLeft.png"
            ),
            getX(), getY(), 150, 150,
            64, 64, 8, 3, 0
        ));

        a_dash.cur--;
        a_dash.frame = 20;
    }

    // Jump held key
    if (moveset.jump && map->MapInput->getKeyPress(4) &&
        (jump.cur || state.hug_wall) && jump.ceiling_min >= 15 &&
        !g_dash.frame && !a_dash.frame && !move.decel &&
        !state.crawl_lock && !jump.knockout)
    {
        map->MapInput->setKeyHold(4, true);

        setY(getY() + 10);
        setVelY(
            (jump.cur == jump.max || jump.coyote_fail) ? 6.5 : 5
        );

        state.on_ground = 0;
        if (state.on_ice) condition.jump_on_ice = 1;
        if (!state.hug_wall) jump.cur--;

        // Particle effect
        if (jump.super == jump.super_max)
        {
            map->ParticleBackVec.push_back(new ParticleEffect(
                loadTexture(
                    "res/ParticleSheet/NakuEffect/SuperJumpSmoke.png"),
                move.hitX(), move.hitY(), 150, 36,
                118, 29, 8, 5, 0
            ));

            setVelY(7.3);
        } else if (state.on_ground)
            map->ParticleBackVec.push_back(new ParticleEffect(
                loadTexture(
                    "res/ParticleSheet/NakuEffect/JumpSmoke.png"),
                getX(), getY() - 24, 50, 50,
                14, 12, 8, 5, 0
            ));

        // Wall jump
        a_dash.lock = 0;
        if (state.hug_wall)
        {
            map->ParticleBackVec.push_back(new ParticleEffect(
                loadTexture(
                    state.hug_wall > 0 ?
                    "res/ParticleSheet/NakuEffect/JumpWallRight.png" :
                    "res/ParticleSheet/NakuEffect/JumpWallLeft.png"),
                getX(), getY(), 50, 50,
                25, 25, 7, 3, 0
            ));

            setVelX(8 * state.hug_wall);
            setVelY(4);
            setX(getX() + getHitWidth() * state.hug_wall / 2);

            a_dash.cur = a_dash.max;
            a_dash.lock = -state.hug_wall;
        }

        state.hug_wall = 0;
    }

// ======================== MOVEMENT LOGIC ==============================

    // Velocity
    move.vel_max = 6.5;
    move.vel_max*= ((state.on_ice || condition.jump_on_ice) ? 1.2 : 1) *
                (combat.weapon_equip ? .8 : 1) *
                (combat.charge_time ? .8 : 1);
    // Acceleration x
    setAccelX(  (state.on_ice ? 0.06 : 0.1) *
                (combat.weapon_equip ? .8 : 1) *
                (combat.charge_time ? .8 : 1));
    // Acceleration y
    setAccelY(  ((map->MapInput->getKeyHold(4) &&
                getVelY() > 0) ? -.1 : -.2) *
                (combat.weapon_equip ? 1.2 : 1) *
                (combat.charge_time ? 1.2 : 1));

    // Velocity X Correction 😭
    // - Check the time spent over speed cap
    if (abs(getVelX()) > move.vel_max) move.vel_over_time++;
    else                            move.vel_over_time = 0;
    // - Self correct speed
    if (move.vel_over_time > move.vel_over_max)
    {
        if (getVelX() > move.vel_max)
            setVelX(getVelX() - (getVelX() - move.vel_max) / 50);
        if (getVelX() < -move.vel_max)
            setVelX(getVelX() - (getVelX() + move.vel_max) / 50);
    }

    // Terminal Velocity
    if (getVelY() + getAccelY() > jump.terminal)
        setVelY(getVelY() + getAccelY());
    // No Velo Y on ground
    if (state.on_ground) setVelY(0);
    // Slow but painful Velo Y
    if (state.hug_wall) setVelY(-1);

    // SUPER JUMP
    if (move.crawl && !state.crawl_lock && !getVelX())
        jump.super += jump.super < jump.super_max;
    else jump.super = 0;

    // Ground dash
    if (g_dash.frame)
    {
        g_dash.frame--;
        if (g_dash.frame) setVelX(18 * dir);
        else setVelX(move.vel_max * dir * 1.1);
    }
    if (g_dash.delay > 0) g_dash.delay--;

    // a_Dashing
    if (a_dash.frame)
    {
        a_dash.frame--;
        if (a_dash.frame) setVelX(20 * dir);
        else setVelX(move.vel_max * dir * 1.05);
        setVelY(0);
    }

    // Jump knock out
    if (jump.knockout > 0) jump.knockout--;

    // Coyote Jump
    if (!state.on_ground &&
        jump.cur == jump.max)
    {
        if (jump.coyote < jump.coyote_max)
            jump.coyote++;
        else
        {
            jump.coyote_fail = 1;
            jump.cur = jump.max - 1;
        }
    }
    else jump.coyote = 0;

    // Reset Stuff when land on ground
    if (state.on_ground)
    {
        condition.jump_on_ice = 0;

        jump.cur = jump.max;
        jump.coyote_fail = 0;

        a_dash.lock = 0;
        a_dash.cur = a_dash.max;
    }

    // Setting Position
    if (godmode) return;
    objectStandardMovement(1);
}

void Player::playerCombat(Map *map)
{
// ======================== COMBAT INPUT ==============================

    // Weapon equipment
    if (map->MapInput->getKeyHold(7) && !combat.weapon_equip_delay &&
        state.on_ground)
    {
        setSprIndex(0);
        combat.weapon_equip_frame = 24;
        combat.weapon_equip_delay = combat.weapon_equip_delay_max;
        combat.weapon_equip = !combat.weapon_equip;
    };
    // Weapon draw ("draw" weapon, not "draw" painting) delay
    if (combat.weapon_equip_delay > 0)
        combat.weapon_equip_delay --;
    if (combat.weapon_equip_frame) 
        combat.weapon_equip_frame --;

    // Special Jelly Projectile
    if (combat.weapon_equip && map->MapInput->getKeyPress(8))
    {
        map->MapInput->setKeyHold(8, true);

        map->ProjectileVec.push_back(new Projectile(
            "res/NakuSheet/NakuSquid.png",
            getX(), getY(), 16, 16,
            32, 32,
            getVelX()*.8 + draw_prop.right*2 - 1,
            getVelY() + 10, 0, -.2,
            10, 1000, -1,
            1, 0, 0,
            4, 10
        ));
    }

// ======================== COMBAT LOGIC ==============================

    // Invincibility frame
    if (combat.invincible)
        combat.invincible--;

    // Invulnerable frame
    if (combat.invulnerable) {
        combat.invulnerable--;

        if (combat.invulnerable > combat.invulnerable_max * .8)
        {
            // When got hit reset all movement and stuff
            setVelX(0);
            setVelY(0);

            a_dash.frame = 0;
            g_dash.frame = 0;

            combat.charge_time = 0;
            combat.combo_time = 0;
            combat.time = 0;
            combat.index = 0;
        }
        SDL_SetTextureAlphaMod(draw_prop.CurrentTexture, (combat.invulnerable % 15 > 0) ? 200 : 160);
    }

    if (combat.time > 0)
        combat.time --;
    else
        combat.time = 0;
    
    if (combat.combo_time > 0)
        combat.combo_time--;
    else
    {
        combat.combo_time = 0;
        combat.index = 0;
    }

    if (combat.delay > 0)
        combat.delay --;
    else
        combat.delay = 0;

    if (!combat.weapon_equip || combat.weapon_equip_frame) return;

    // =================== Combat hitbox handler ===================
    if (!combat.time && !a_dash.frame && !g_dash.frame)
    {
        setCombatHit({});
        combat.parry_error = 10;
    }

    if (a_dash.frame)
        setCombatHit({
            30, 30, 
            draw_prop.right ? 0 : 80,
            draw_prop.right ? 80 : 0,
            10
        });

    if (g_dash.frame)
        setCombatHit({
            20, 20,
            draw_prop.right ? 0 : 100,
            draw_prop.right ? 100 : 0,
            move.crawl ? 20 : 12
        });

    if (combat.index == 1)
    {
        setCombatHit({
            40, 40,
            draw_prop.right? 0 : 100,
            draw_prop.right? 100 : 0,
            10
        });
        combat.parry_error = 3;
    }

    if (combat.index == 2)
    {
        setCombatHit({
            15, 15,
            draw_prop.right ? 0 : 120,
            draw_prop.right ? 120 : 0,
            20
        });
        combat.parry_error = 1;
    }

    if (combat.index == 3)
    {
        setCombatHit({
            80, 60,
            draw_prop.right ? 0 : 130,
            draw_prop.right ? 130 : 0,
            30
        });
        combat.parry_error = 0;
    }

    if (combat.index == 4)
    {
        setCombatHit({76, 0, 64, 64, 15});
        combat.parry_error = 40;
    }

    if (combat.index == 5)
    {
        setCombatHit({
            64, 64, draw_prop.right?0:93, draw_prop.right?93:0, 15
        });
        combat.parry_error = 20;
    }

    // =================== Combat Attack Pattern ===================

    // On ground
    if (!combat.delay && !move.crawl && !g_dash.frame &&
        map->MapInput->getKeyThresPeak(6) &&
        map->MapInput->getKeyThresPeak(6) < 100)
    {
        map->MapInput->resetKeyThresPeak(6);

        if (!state.hug_wall && !map->MapInput->getKeyHold(0))
        {
            if (!combat.combo_time && !combat.index)
            {
                combat.index = 1;
                combat.time = 15;
                combat.combo_time = 40;
                draw_prop.end_lock = 0;

                setVelX(getVelX() * .8);
                setVelY(state.on_ground ? 0 : 1);
            }
            else if (!combat.time && combat.index == 1 && combat.combo_time)
            {
                combat.index = 2;
                combat.time = 15;
                combat.combo_time = 15;
                combat.delay = 35;
                draw_prop.end_lock = 0;

                setVelX(getVelX() * .4);
                setVelY(state.on_ground ? 0 : 1);
            }
        }
        else if (!state.hug_wall && map->MapInput->getKeyHold(0))
        {
            if (!combat.combo_time && !combat.index)
            {
                combat.index = 4;
                combat.time = 15;
                combat.combo_time = 15;
                combat.delay = state.on_ground ? 40 : 70;
                draw_prop.end_lock = 0;

                setVelY(3);
            }
        }
        else if (state.hug_wall)
        {
            if (!combat.combo_time && !combat.index)
            {
                combat.index = 5;
                combat.time = 12;
                combat.combo_time = 40;
                draw_prop.end_lock = 0;
            }
        }
    }

    // Charge Attack
    if (combat.charge_time > 0)
    {
        combat.index = 3;

        if (!map->MapInput->getKeyHold(6) &&
            combat.charge_time > 50)
        {
            combat.time = 10;
            combat.combo_time = 10;
            combat.delay = 150;

            draw_prop.end_lock = 0;
        }
    }

    if (!combat.delay && !combat.time &&
        map->MapInput->getKeyThreshold(6, 100) &&
        !draw_prop.end_lock && !move.crawl &&
        !state.hug_wall &&
        !a_dash.frame && !g_dash.frame)
        combat.charge_time ++;
    else
        combat.charge_time = 0;
}

void Player::playerHitBox()
{
    if (!move.crawl &&
        !g_dash.frame &&
        !state.crawl_lock)
    {
        setHitWidth(58);
        setHitHeight(80);
        move.hit_offset_y = 0;
    }
    else
    {
        setHitWidth(78);
        setHitHeight(40);
        move.hit_offset_y = -20;
    }
}

void Player::playerGetHit(Map *map, int dmg)
{
    if (combat.invulnerable || combat.invincible) return;

    // map->ParticleBackVec.push_back(new ParticleEffect(
    //     loadTexture(CFG->RENDERER,
    //         "res/ParticleSheet/NakuEffect/BloodSplatter.png"),
    //     getX(), getY(), 300, 300,
    //     100, 100, 6, 3, 4, 0
    // ));

    // map->ParticleBackVec.push_back(new ParticleEffect(
    //     loadTexture(CFG->RENDERER,
    //         "res/ParticleSheet/Explode.png"),
    //     getX(), getY(), 300, 300,
    //     100, 100, 10, 7, 3, 0
    // ));

    combat.invulnerable = combat.invulnerable_max;
    hp -= dmg;
}
// ==============================================================================
// ======================= DEVELOPER MODE (STAFF ONLY) ==========================
// ==============================================================================

void Player::playerDeveloper(Map *map)
{
    // Really sorry but grid straight up dont work in other scale mode
    // Im not doing the math bruh
    // (UPDATE: NEVER FUCKING MIND FUCK SCALING LMAO)
    if (grid)
    {
        // Draw grid line
        SDL_SetRenderDrawColor(CFG->RENDERER, 0, 255, 0, 255);

        int gridLineX = camera.unfocus_x ? 0 :
            int(getX()) % 64 - Camera::playerShiftX(this);
        int gridLineY = camera.unfocus_y ? 0 :
            int(getY()) % 64 + Camera::playerShiftY(this);

        for (int i = 0; i < int(CFG->WIDTH / 60); i++)
        {
            int drawGridX = i * 64 - gridLineX;
            SDL_RenderDrawLine(CFG->RENDERER, drawGridX - 1, 0,
                                drawGridX - 1, CFG->HEIGHT);
            SDL_RenderDrawLine(CFG->RENDERER, drawGridX, 0,
                                drawGridX, CFG->HEIGHT);
            SDL_RenderDrawLine(CFG->RENDERER, drawGridX + 1, 0,
                                drawGridX + 1, CFG->HEIGHT);
        }
        for (int i = 0; i < int(CFG->HEIGHT / 60); i++)
        {
            int drawGridY = i * 64 + gridLineY;
            SDL_RenderDrawLine(CFG->RENDERER, 0, drawGridY - 1,
                                CFG->WIDTH, drawGridY - 1);
            SDL_RenderDrawLine(CFG->RENDERER, 0, drawGridY,
                                CFG->WIDTH, drawGridY);
            SDL_RenderDrawLine(CFG->RENDERER, 0, drawGridY + 1,
                                CFG->WIDTH, drawGridY + 1);
        }

        CFG->addDevlog("MOUSE", 41);
        CFG->addDevlog(
            "X: " + std::to_string(map->MapInput->getMMapX(this)) +
            " - Y: " + std::to_string(map->MapInput->getMMapY(this))
        ,31);

        CFG->addDevlog("Player", 42);
        CFG->addDevlog(
            "X: " + std::to_string(getGridX()) +
            " - Y: " + std::to_string(getGridY())
        ,32);
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    // ===============DEVELOPER input===============
    // GODMODE
    if (state[toggle_code[0]] && !toggle_hold[0])
    {
        toggle_hold[0] = true;
        godmode = !godmode;
    }
    if (!state[toggle_code[0]]) toggle_hold[0] = false;

    if (godmode)
    {
        int vel_developer = state[SDL_SCANCODE_LCTRL] ? 20 : 4;
        if (state[SDL_SCANCODE_W]) setY(getY() + vel_developer);
        if (state[SDL_SCANCODE_S]) setY(getY() - vel_developer);
        if (state[SDL_SCANCODE_D]) setX(getX() + vel_developer);
        if (state[SDL_SCANCODE_A]) setX(getX() - vel_developer);
    }
    // DISPLAY GRID
    if (state[toggle_code[1]] && !toggle_hold[1])
    {
        toggle_hold[1] = true;
        grid = !grid;
    };
    if (!state[toggle_code[1]]) toggle_hold[1] = false;
}

bool Player::getGodmode() { return godmode; }

// ==== Note ====
// Reason for the absence of player sprite in update
// is to avoid a lag in drawing other decoration/block layer caused
// by intensive <player> calculation
void Player::playerUpdate(Map *map)
{
    playerMovement(map);
    playerCombat(map);
    playerHitBox();
    draw_prop.playerDrawProperty(map);
}

void Player::playerEnableAllMoveset()
{
    moveset.move = true;
    moveset.jump = true;
    moveset.crawl = true;
    moveset.g_dash = true;
    moveset.a_dash = true;
    moveset.hug_wall = true;
}