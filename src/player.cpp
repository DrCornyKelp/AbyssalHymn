#include <map.h>

// Destructor
Player::~Player()
{ psprite.clearTexture(); }
// Constructor
Player::Player(bool mc) : Object2D(), MAIN(mc)
{
    // Nakuru normal mvoement
    psprite.RightTexture = CFG->loadTexture("assets/NakuSheet/NakuRight.png");
    psprite.LeftTexture = CFG->loadTexture("assets/NakuSheet/NakuLeft.png");

    // Nakuru holding weapon
    psprite.RightWeaponTexture = CFG->loadTexture("assets/NakuSheet/NakuRightWeapon.png");
    psprite.LeftWeaponTexture = CFG->loadTexture("assets/NakuSheet/NakuLeftWeapon.png");
}

// ============================ PLAYER MOVESET ============================

void PlayerMoveset::enableAll()
{
    move = 1;
    jump = 1;
    crawl = 1;
    g_dash = 1;
    a_dash = 1;
    hug_wall = 1;
}
void PlayerMoveset::disableAll()
{
    move = 0;
    jump = 0;
    crawl = 0;
    g_dash = 0;
    a_dash = 0;
    hug_wall = 0;
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
{ return player->hitbox.x + hit_offset_x; }
int PlayerMoving::hitY()
{ return player->hitbox.y + hit_offset_y; }

// ============================ PLAYER DRAW PROP ============================

void PlayerSprite::clearTexture()
{
    Object2D::deleteTextures({
        CurrentTexture,
        RightTexture, LeftTexture,
        RightWeaponTexture, LeftWeaponTexture
    });
}

void PlayerSprite::setAct(int idx, bool r)
{
    if (index != idx || right != r)
    { index = idx; right = r; }
}

void PlayerSprite::setSprite(int m_index, int m_frame)
{
    player->sprite.sim = m_index;
    player->sprite.sfm = m_frame;
}

void PlayerSprite::setSpriteAlpha(int alp)
{
    if (alpha != alp)
    {
        alpha = alp;
        SDL_SetTextureAlphaMod(CurrentTexture, alpha);
    }
}

void PlayerSprite::setEndLock(bool lock)
{
    if (lock && !end_lock)
    {
        player->sprite.sf = 0;
        player->sprite.si = 0;
    }
    end_lock = lock;
}

void PlayerSprite::setActSprElock(int1D act, int1D spr, short lock)
{
    setAct(act[0], act[1]);
    setSprite(spr[0], spr[1]);
    // Lock: -1: no lock, 0: ignore, 1: lock
    if (lock) setEndLock(lock > 0);
}

void PlayerSprite::drawProp()
{
    // ======================== SRPITES ===========================
    // Set index and stuff
    right = player->vel.x > .2 ? 1 :
            player->vel.x < -.2 ? 0 : right;

    // Movement
    if (!player->combat.index)
    {
        // ============= MOVEMENT SPRITE =============

        // Idling
        if (abs(player->vel.x) <= .2)
            setActSprElock({0, right}, {2, 64});
        // Moving
        else
            setActSprElock(
                {1, right},
                {8, 30 - int(abs(player->vel.x) * 4)}
            );
        // Decelerating
        if (player->move.decel != 0)
            setActSprElock({2, player->move.decel > 0}, {2, 2});
        // Jumping
        if (!player->jump.coyote && !player->state.on_ground)
            setActSprElock({3, right}, {
                (player->vel.y > .2 ? 4 : 8),
                (player->vel.y > .2 ? 16 : 8)
            });
        // Ground Dashing
        if (player->g_dash.frame)
            setActSprElock({4, right}, {8, 3}, 1);
        // Air Dashing
        if (player->a_dash.frame)
            setActSprElock({5, right}, {4, 10}, 1);
        // Crawling
        if (player->move.crawl &&
            !(player->g_dash.frame && player->state.crawl_lock))
            setActSprElock({6, right}, {
                (abs(player->vel.x) > 0 ? 4 : 1), 8
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
            switch (player->INPUT.attack.state)
            {
            case 0:
                setActSprElock({13, right}, {4, 2}, 1);
                break;

            case 1:
                setActSprElock({12, right}, {
                    player->vel.x ? 4 : 1,
                    30 - int(abs(player->vel.x) * 4)
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

    player->hitbox.w = player->combat.weapon_equip ? 64 : 32;

    // Update Sprite Properties
    player->setSprite(end_lock);

    desRect = {
        Camera::objectDrawX(player->MULTI->MAIN, player) - int(player->hitbox.w*3/2),
        Camera::objectDrawY(player->MULTI->MAIN, player) - int(player->hitbox.w*2),
        int(player->hitbox.w*4), int(player->hitbox.w*4)
    };
    srcRect = {
        player->sprite.si * int(player->hitbox.w),
        index * int(player->hitbox.w),
        int(player->hitbox.w), int(player->hitbox.w)
    };

    if (!player->combat.invulnerable)
        SDL_SetTextureAlphaMod(CurrentTexture, 255);
}

void PlayerSprite::draw()
{
    SDL_RenderCopy(CFG->RENDERER, CurrentTexture, &srcRect, &desRect);
}

// ============================ SOUND EFFECT =============================

void PlayerSFX::updateWalkSFX()
{
    // Check player state
    if (player->state.on_ground && player->vel.x &&
        !player->move.crawl && !player->g_dash.frame &&
        !player->move.decel)
    {
        // Counting steps based on sprite index
        if (player->sprite.si != walk_sprite)
        {
            walk_step ++;
            walk_sprite = player->sprite.si;
        }

        // Play sound effect after enough steps
        if (walk_step > 1)
        {
            walk_step = 0;

            // Play random walk sound
            walk_index = CFG->randomInt(3);
            switch (walk_index)
            {
                case 0: walk0.play(); break;
                case 1: walk1.play(); break;
                case 2: walk2.play(); break;
            }
        }
    }
}

void PlayerSFX::updateSFX()
{
    updateWalkSFX();
}

// ============================ PLAYER CAMERA ============================

void PlayerCamera::updateStatic()
{
    mid.x = 0; mid.y = 0;
    ease.x = 0; ease.y = 0;
    effect.x = 0; effect.y = 0;
    offset.x = 0; offset.y = 0;
    unfocus.x = 0; unfocus.y = 0;
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

// Center Offset
ObjectXY PlayerCamera::getCenterOffset() {
    ObjectXY center_off = {0, 0};
    for (Player *playersub : player->MULTI->Players)
    {
        center_off.x += Object2D::distX(
            player, playersub
        );
        center_off.y += Object2D::distY(
            player, playersub
        );
    }
    center_off.x /= player->MULTI->PlayerCount;
    center_off.y /= player->MULTI->PlayerCount;

    return center_off;
};
// Camera Focus Trigger
ObjectXYf PlayerCamera::getFocusTrigger() {
    return {
        player->hitbox.x - shift.x - center_off.x,
        player->hitbox.y - shift.y - center_off.y
    };
}
// Camera Shift
ObjectXYf PlayerCamera::getShift() {
    return {
        ease.x + effect.x,
        ease.y + effect.y
    };
}

void PlayerCamera::playerCameraFocus()
{
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
        focus_trigger.x < focus_true.left)
    {
        unfocus.x = 1;
        unfocus_offset.x = focus_true.left;
        mid.x = player->hitbox.x - focus_true.left;
    }
    // Boundary right
    else if (focus_dir.right &&
        focus_trigger.x > focus_true.right)
    {
        unfocus.x = 1;
        unfocus_offset.x = focus_true.right;
        mid.x = player->hitbox.x - focus_true.right;
    }
    else
    {
        unfocus.x = 0;
        mid.x = 0;
    }

    // === Focus Y ===

    // Boundary Down
    if (focus_dir.down &&
        focus_trigger.y < focus_true.down)
    {
        unfocus.y = 1;
        unfocus_offset.y = focus_true.down;
        mid.y = player->hitbox.y - focus_true.down;
    }
    // Boundary Up
    else if (focus_dir.up &&
        focus_trigger.y > focus_true.up)
    {
        unfocus.y = 1;
        unfocus_offset.y = focus_true.up;
        mid.y = player->hitbox.y - focus_true.up;
    }
    else
    {
        unfocus.y = 0;
        mid.y = 0;
    }
}

void PlayerCamera::updateDynamic()
{
    playerCameraFocus();

    // Update the values
    shift = getShift(); // Include effect + ease
    center_off = getCenterOffset();
    focus_trigger = getFocusTrigger();
    // Total offset from center
    offset.x = shift.x + mid.x + center_off.x;
    offset.y = shift.y + mid.y + center_off.y;

    // EASING EFFECT FOR MOVEMENT FOR BETTER LOOKAHEAD

    if (!unfocus.x)
    {
        float ease_x_max =  (player->combat.weapon_equip ? 64 : 96) +
                            // Velociy pass a cap
                            (player->vel.x>player->move.vel_max ?
                                (player->vel.x - player->move.vel_max)*64 : 0);
        // Damping / Easing effect X
        if (player->psprite.right && ease.x > -ease_x_max)
            ease.x -= abs(player->vel.x / 5);
        if (!player->psprite.right && ease.x < ease_x_max)
            ease.x += abs(player->vel.x / 5);
        // Turn off easing effect
        if (!player->vel.x || abs(ease.x) > ease_x_max)
            ease.x -= ease.x / 100;

        // Dash Feel Faster
        if (player->g_dash.frame || player->a_dash.frame)
        {
            if (abs(effect.x) < 64)
                effect.x += player->vel.x > 0 ? -2 : 2;
        }
        else if (effect.x)
            effect.x -= effect.x / 40;
    }

    if (!unfocus.y)
    {
        float ease_y_max =  (player->combat.weapon_equip ? 32 : 64);
        // Damping / Easing effect Y
        if (ease.y > -ease_y_max && player->vel.y > 0)
            ease.y -= abs(player->vel.y / 5);
        if (ease.y < ease_y_max && player->vel.y < 0)
            ease.y += abs(player->vel.y / 5);
        // Turn off easing effect
        if (!player->vel.y || abs(ease.y) > ease_y_max)
            ease.y -= ease.y / 100;
    }
}

void Player::playerMovement(Map *map)
{
// ======================== Helpful values ==============================
    short dir = psprite.right ? 1 : -1;

// ======================== MOVEMENT INPUT ==============================
    // Moving L/R
    if (moveset.move && !g_dash.frame && !a_dash.frame && !move.crawl)
    {
        if (INPUT.moveL.state && state.hug_wall < 1)
        {
            // Release from wall
            if (state.hug_wall) hitbox.x -= 4;
            state.hug_wall = 0;

            move.decel = vel.x > 1;
            if (vel.x - accel.x > -move.vel_max)
                vel.x -= accel.x * (move.decel ? 2.5 : 1);
        }

        if (INPUT.moveR.state && state.hug_wall > -1)
        {
            if (state.hug_wall) hitbox.x += 4;
            state.hug_wall = 0;

            move.decel = -(vel.x < -1);
            if (vel.x + accel.x < move.vel_max)
                vel.x += accel.x * (move.decel ? 2.5 : 1);
        }
    }

    // Not moving anymore
    if (!INPUT.moveL.state && !INPUT.moveR.state &&
        !g_dash.frame && !a_dash.frame)
    {
        if (abs(vel.x) >= accel.x)
            vel.x -= accel.x * dir;
        else
            vel.x = 0;
    }

    // No more deceleration
    if ((!INPUT.moveL.state && move.decel > 0) ||
        (!INPUT.moveR.state && move.decel < 0))
        move.decel = 0;

    // Crawling
    move.crawl= moveset.crawl && INPUT.moveD.state &&
                state.on_ground && !move.decel &&
                !g_dash.delay && !g_dash.frame &&
                abs(vel.x) < move.vel_max / 2;
    move.crawl = state.crawl_lock || move.crawl;

    if (move.crawl && INPUT.moveL.state && !g_dash.frame)
        vel.x = - move.vel_crawl;
    if (move.crawl && INPUT.moveR.state && !g_dash.frame)
        vel.x = move.vel_crawl;

    // Ground dash (more like sliding but whatever)
    if (moveset.g_dash && INPUT.dash.press() && !g_dash.delay &&
        !state.crawl_lock && state.on_ground &&
        !g_dash.frame && !combat.index && !combat.weapon_equip_frame)
    {
        INPUT.dash.hold = 1;

        map->appendParticle(new ParticleEffect(
            CFG->loadTexture(psprite.right ?
                "assets/ParticleSheet/NakuEffect/GDashSmokeRight.png" :
                "assets/ParticleSheet/NakuEffect/GDashSmokeLeft.png"
            ),
            hitbox.x, hitbox.y, 100, 71,
            59, 42, 7, 5, 0
        ));

        g_dash.frame = move.crawl ? 32 : 24;
        g_dash.delay = move.crawl ? 40 : 25;
    }

    // Air dash
    if (moveset.a_dash && INPUT.dash.press() &&
        !a_dash.frame && a_dash.cur &&
        !state.on_ground && !state.hug_wall &&
        !combat.index && !combat.weapon_equip_frame &&
        (   (vel.x > 0 && a_dash.lock != 1) ||
            (vel.x < 0 && a_dash.lock != -1) )
        )
    {
        INPUT.dash.hold = 1;

        map->appendParticle(new ParticleEffect(
            CFG->loadTexture(psprite.right ?
                "assets/ParticleSheet/NakuEffect/ADashSmokeRight.png" :
                "assets/ParticleSheet/NakuEffect/ADashSmokeLeft.png"
            ),
            hitbox.x, hitbox.y, 150, 150,
            64, 64, 8, 3, 0
        ));

        a_dash.cur--;
        a_dash.frame = 20;
    }

    // Jump held key
    if (moveset.jump && INPUT.jump.press() &&
        (jump.cur || state.hug_wall) && jump.ceiling_min >= 15 &&
        !g_dash.frame && !a_dash.frame && !move.decel &&
        !state.crawl_lock && !jump.knockout)
    {
        INPUT.jump.hold = 1;

        hitbox.y += 10;
        vel.y = (jump.cur == jump.max || jump.coyote_fail) ? 6.5 : 5;

        state.on_ground = 0;
        if (state.on_ice) state.jump_on_ice = 1;
        if (!state.hug_wall) jump.cur--;

        // Particle effect
        if (jump.super == jump.super_max)
        {
            map->appendParticle(new ParticleEffect(
                CFG->loadTexture(
                    "assets/ParticleSheet/NakuEffect/SuperJumpSmoke.png"),
                move.hitX(), move.hitY(), 150, 36,
                118, 29, 8, 5, 0
            ));

            vel.y = 7.3;
        } else if (state.on_ground)
            map->appendParticle(new ParticleEffect(
                CFG->loadTexture(
                    "assets/ParticleSheet/NakuEffect/JumpSmoke.png"),
                hitbox.x, hitbox.y - 24, 50, 50,
                14, 12, 8, 5, 0
            ));

        // Wall jump
        a_dash.lock = 0;
        if (state.hug_wall)
                {
                    map->appendParticle(new ParticleEffect(
                        CFG->loadTexture(
                            state.hug_wall > 0 ?
                            "assets/ParticleSheet/NakuEffect/JumpWallRight.png" :
                            "assets/ParticleSheet/NakuEffect/JumpWallLeft.png"),
                        hitbox.x, hitbox.y, 50, 50,
                        25, 25, 7, 3, 0
                    ));

                    vel.x = 8 * state.hug_wall;
                    vel.y = 4;
                    hitbox.x += hitbox.hw * state.hug_wall / 2;

                    a_dash.cur = a_dash.max;
                    a_dash.lock = -state.hug_wall;
                }

                state.hug_wall = 0;
            }

        // ======================== MOVEMENT LOGIC ==============================

            // Velocity
            move.vel_max = 6.5;
            move.vel_max*= ((state.on_ice || state.jump_on_ice) ? 1.2 : 1) *
                        (combat.weapon_equip ? .8 : 1) *
                        (combat.charge_time ? .8 : 1);
            // Acceleration x
            accel.x =  (state.on_ice ? .06 : .1) *
                        (combat.weapon_equip ? .8 : 1) *
                        (combat.charge_time ? .8 : 1);
            // Acceleration y
            accel.y =  ((INPUT.jump.hold && vel.y > 0) ? -.1 : -.2) *
                        (combat.weapon_equip ? 1.2 : 1) *
                        (combat.charge_time ? 1.2 : 1);

            // Velocity X Correction 😭
            // - Check the time spent over speed cap
            if (abs(vel.x) > move.vel_max) move.vel_over_time++;
            else                               move.vel_over_time = 0;
            // - Self correct speed
            if (move.vel_over_time > move.vel_over_max)
            {
                if (vel.x > move.vel_max)
                    vel.x = vel.x - (vel.x - move.vel_max) / 50;
                if (vel.x < -move.vel_max)
                    vel.x = vel.x - (vel.x + move.vel_max) / 50;
            }

            // Terminal Velocity
            if (vel.y + accel.y > jump.terminal)
                vel.y = vel.y + accel.y;
            // No Velo Y on ground
            if (state.on_ground) vel.y = 0;
            // Slow but painful Velo Y
            if (state.hug_wall) vel.y = -1;

            // SUPER JUMP
            if (move.crawl && !state.crawl_lock && !vel.x)
                jump.super += jump.super < jump.super_max;
            else jump.super = 0;

            // Ground dash
            if (g_dash.frame)
            {
                g_dash.frame--;
                if (g_dash.frame) vel.x = 18 * dir;
                else vel.x = move.vel_max * dir * 1.1;
            }
            if (g_dash.delay > 0) g_dash.delay--;

            // a_Dashing
            if (a_dash.frame)
            {
                a_dash.frame--;
                if (a_dash.frame) vel.x = 20 * dir;
                else vel.x = move.vel_max * dir * 1.05;
                vel.y = 0;
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
                state.jump_on_ice = 0;

                jump.cur = jump.max;
                jump.coyote_fail = 0;

                a_dash.lock = 0;
                a_dash.cur = a_dash.max;
            }

            // Setting Position
            if (dev.godmode) return;
            objectStandardMovement(1);
        }

        void Player::playerCombat(Map *map)
        {
        // ======================== COMBAT INPUT ==============================

            // Weapon equipment
            if (INPUT.equip.state && !combat.weapon_equip_delay &&
                state.on_ground)
            {
                sprite.si = 0;
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
            if (combat.weapon_equip && INPUT.proj.press())
            {
                INPUT.proj.hold = 1;

                map->ProjectileVec.push_back(new Projectile(
                    "assets/NakuSheet/NakuSquid.png",
                    hitbox.x, hitbox.y + 50, 16, 16,
                    32, 32,
                    vel.x*.8 + psprite.right*2 - 1,
                    vel.y + 10, 0, -.2,
                    10, 1000, 0,
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
                    vel.x = 0;
                    vel.y = 0;

                    a_dash.frame = 0;
                    g_dash.frame = 0;

                    combat.charge_time = 0;
                    combat.combo_time = 0;
                    combat.time = 0;
                    combat.index = 0;
                }
                SDL_SetTextureAlphaMod(psprite.CurrentTexture, (combat.invulnerable % 15 > 0) ? 200 : 160);
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
                combatbox = {};
                combat.parry_error = 10;
            }

            if (a_dash.frame)
                combatbox = {
                    30, 30, 
                    psprite.right ? 0 : 80,
                    psprite.right ? 80 : 0,
                    10
                };

            if (g_dash.frame)
                combatbox = {
                    20, 20,
                    psprite.right ? 0 : 100,
                    psprite.right ? 100 : 0,
                    move.crawl ? 20 : 12
                };

            if (combat.index == 1)
            {
                combatbox = {
                    40, 40,
                    psprite.right? 0 : 100,
                    psprite.right? 100 : 0,
                    10
                };
                combat.parry_error = 3;
            }

            if (combat.index == 2)
            {
                combatbox = {
                    15, 15,
                    psprite.right ? 0 : 120,
                    psprite.right ? 120 : 0,
                    20
                };
                combat.parry_error = 1;
            }

            if (combat.index == 3)
            {
                combatbox = {
                    80, 60,
                    psprite.right ? 0 : 130,
                    psprite.right ? 130 : 0,
                    30
                };
                combat.parry_error = 0;
            }

            if (combat.index == 4)
            {
                combatbox = {76, 0, 64, 64, 15};
                combat.parry_error = 40;
            }

            if (combat.index == 5)
            {
                combatbox = {
                    64, 64, psprite.right?0:93, psprite.right?93:0, 15
                };
                combat.parry_error = 20;
            }

            // =================== Combat Attack Pattern ===================

            // On ground
            if (!combat.delay && !move.crawl && !g_dash.frame &&
                INPUT.attack.threspeak &&
                INPUT.attack.threspeak < 100)
            {
                INPUT.attack.threspeak = 0;

                if (!state.hug_wall && !INPUT.moveU.state)
                {
                    if (!combat.combo_time && !combat.index)
                    {
                        combat.index = 1;
                        combat.time = 15;
                        combat.combo_time = 40;
                        psprite.end_lock = 0;

                        vel.x = vel.x * .8;
                        vel.y = state.on_ground ? 0 : 1;
                    }
                    else if (!combat.time && combat.index == 1 && combat.combo_time)
                    {
                        combat.index = 2;
                        combat.time = 15;
                        combat.combo_time = 15;
                        combat.delay = 35;
                        psprite.end_lock = 0;

                        vel.x = vel.x * .4;
                        vel.y = state.on_ground ? 0 : 1;
                    }
                }
                else if (!state.hug_wall && INPUT.moveU.state)
                {
                    if (!combat.combo_time && !combat.index)
                    {
                        combat.index = 4;
                        combat.time = 15;
                        combat.combo_time = 15;
                        combat.delay = state.on_ground ? 40 : 70;
                        psprite.end_lock = 0;

                        vel.y = 3;
                    }
                }
                else if (state.hug_wall)
                {
                    if (!combat.combo_time && !combat.index)
                    {
                        combat.index = 5;
                        combat.time = 12;
                        combat.combo_time = 40;
                        psprite.end_lock = 0;
                    }
                }
            }

            // Charge Attack
            if (combat.charge_time > 0)
            {
                combat.index = 3;

                if (!INPUT.attack.state &&
                    combat.charge_time > 50)
                {
                    combat.time = 10;
                    combat.combo_time = 10;
                    combat.delay = 150;

                    psprite.end_lock = 0;
                }
            }

            if (!combat.delay && !combat.time &&
                INPUT.attack.threspass(100) &&
                !psprite.end_lock && !move.crawl &&
                !state.hug_wall &&
                !a_dash.frame && !g_dash.frame)
                combat.charge_time ++;
            else
                combat.charge_time = 0;
        }

        // Stop Player Current State
        void Player::setStatic()
        {   
            // Reset Sprite State
            sprite.sf = 0;
            sprite.si = 0;
            setSprite(0);
            // Reset Movement
            vel.x = 0;
            vel.y = 0;
            move.crawl = 0;
            a_dash.frame = 0;
            g_dash.frame = 0;
            // Reset HitBox
            hitbox.hw = 58;
            hitbox.hh = 80;
            // Reset Combat
            combat.delay = 0;
            combat.combo_time = 0;
            combat.charge_time = 0;
        }

void Player::playerHitBox()
{
    if (!move.crawl &&
        !g_dash.frame &&
        !state.crawl_lock)
    {
        hitbox.hw = 58;
        hitbox.hh = 80;
        move.hit_offset_x = 0;
        move.hit_offset_y = 0;
    }
    else
    {
        hitbox.hw = 78;
        hitbox.hh = 40;
        move.hit_offset_x = -10;
        move.hit_offset_y = -20;
    }
}

void Player::playerGetHit(Map *map, int dmg)
{
    if (combat.invulnerable || combat.invincible) return;

    // map->appendParticle(new ParticleEffect(
    //     CFG->loadTexture(CFG->RENDERER,
    //         "assets/ParticleSheet/NakuEffect/BloodSplatter.png"),
    //     hitbox.x, hitbox.y, 300, 300,
    //     100, 100, 6, 3, 4, 0
    // ));

    // map->appendParticle(new ParticleEffect(
    //     CFG->loadTexture(CFG->RENDERER,
    //         "assets/ParticleSheet/Explode.png"),
    //     hitbox.x, hitbox.y, 300, 300,
    //     100, 100, 10, 7, 3, 0
    // ));

    combat.invulnerable = combat.invulnerable_max;
    hp -= dmg;
}
// ==============================================================================
// ======================= DEVELOPER MODE (STAFF ONLY) ==========================
// ==============================================================================

void PlayerDeveloper::developer(Map *map)
{
    // Really sorry but grid straight up dont work in other scale mode
    // Im not doing the math bruh
    // (UPDATE: NEVER FUCKING MIND FUCK SCALING LMAO)
    if (grid)
    {
        // Draw grid line
        SDL_SetRenderDrawColor(CFG->RENDERER, 0, 255, 0, 255);

        int gridLineX = player->camera.unfocus.x ? 0 :
            int(player->hitbox.x) % 64 -
            player->camera.shift.x -
            player->camera.center_off.x;
        int gridLineY = player->camera.unfocus.y ? 0 :
            int(player->hitbox.y) % 64 -
            player->camera.shift.y -
            player->camera.center_off.y;

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
            "X: " + std::to_string(player->INPUT.mouse.mapX(player)) +
            " - Y: " + std::to_string(player->INPUT.mouse.mapY(player))
        ,31);

        CFG->addDevlog("Player", 42);
        CFG->addDevlog(
            "X: " + std::to_string(player->hitbox.gridX()) +
            " - Y: " + std::to_string(player->hitbox.gridY())
        ,32);
    }

    // =============== DEVELOPER input ===============
    // GODMODE
    if (player->INPUT.f2.press())
    {
        player->INPUT.f2.hold = 1;
        godmode = !godmode;
    }

    if (godmode)
    {
        int vel_developer = player->INPUT.lctrl.state ? 20 : 4;
        if (player->INPUT.moveU.state)
            player->hitbox.y += vel_developer;
        if (player->INPUT.moveD.state)
            player->hitbox.y -= vel_developer;
        if (player->INPUT.moveL.state)
            player->hitbox.x -= vel_developer;
        if (player->INPUT.moveR.state)
            player->hitbox.x += vel_developer;
    }

    // DISPLAY GRID
    if (player->INPUT.f3.press())
    {
        player->INPUT.f3.hold = 1;
        grid = !grid;
    };
}

// ==== Note ====
// Reason for the absence of player sprite in update
// is to avoid a lag in drawing other decoration/block layer caused
// by intensive <player> calculation
void Player::playerUpdate(Map *map)
{
    INPUT.update();

    playerMovement(map);
    playerCombat(map);
    playerHitBox();

    psprite.drawProp();
    sfx.updateSFX();
}