#include <multiplayer.h>

bool Camera::objectIgnore(Player *player, Object2D *obj, bool camIndependent)
{
    if (obj->getIgnore()) return true;

    int colli_x = abs(Object2D::distX(player, obj));
    int colli_y = abs(Object2D::distY(player, obj));

    // Object outside of playable/usuable view
    bool outside_window = 
        colli_x - obj->getWidth() / 2 > CFG->WIDTH * 1.2 ||
        colli_y - obj->getHeight() / 2 > CFG->HEIGHT * 1.2;

    ObjectBox oBox = obj->getBox();
    ObjectBox bBox = player->camera.focus_border;
    ObjectBox dBox = player->camera.focus_dir;

    // Object outside of player cam border
    bool outside_cam = 
        // Object Must "NOT" Depend On Map Cam
        obj->getCamDepend() &&
        // Player Can "NOT" Render Outside Of Map Cam
        !player->camera.outside_render &&
        // For Specific use Case
        !camIndependent && (
        // Box "NOT" Inside Cam
        (oBox.up > bBox.up && dBox.up) ||
        (oBox.down < bBox.down && dBox.down) ||
        (oBox.right > bBox.right && dBox.right) ||
        (oBox.left < bBox.left && dBox.left)
    );

    return outside_window || outside_cam;
}

int Camera::playerShiftX(Player *player)
{
    return  player->camera.ease_x +
            player->camera.effect_x;
}
int Camera::playerShiftY(Player *player)
{
    return  player->camera.ease_y +
            player->camera.vertical_ahead + // Gameplay advantage move
            player->camera.effect_y;
}

int Camera::objectDrawX(Player *player, Object2D *obj)
{
    // X is fine
    int dist_x = Object2D::distX(obj, player);

    return (player->camera.unfocus_x ?
            CFG->WIDTH/2 + obj->getX() - player->camera.unfocus_offset_x - obj->getWidth()/2 :
            CFG->WIDTH/2 + dist_x + player->camera.offset_mid_x - obj->getWidth()/2)
            + Camera::playerShiftX(player);
}
int Camera::objectDrawY(Player *player, Object2D *obj)
{
    // Y focus is fine but unfocus is a piece of shit
    int dist_y = Object2D::distY(obj, player);

    return (player->camera.unfocus_y ?
            CFG->HEIGHT/2 - obj->getY() + player->camera.unfocus_offset_y - obj->getHeight()/2 :
            CFG->HEIGHT/2 - dist_y - player->camera.offset_mid_y - obj->getHeight()/2)
            + Camera::playerShiftY(player);
}

int Camera::playerDrawX(Player *player, int W)
{
    return  CFG->WIDTH/2 + player->camera.offset_mid_x
            - W/2 + playerShiftX(player);
}

int Camera::playerDrawY(Player *player, int H)
{
    return  CFG->HEIGHT/2 - player->camera.offset_mid_y
            - H/2 + playerShiftY(player);
}