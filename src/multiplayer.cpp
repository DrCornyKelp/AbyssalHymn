#include <mulitplayer.h>

Multiplayer::Multiplayer(Player1D playervec) : PlayerVec(playervec)
{}

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