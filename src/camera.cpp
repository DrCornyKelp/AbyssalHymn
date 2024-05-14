#include <multiplayer.h>

bool Camera::renderIgnore(Player *player, Object2D *obj, bool camIndependent)
{
    if (obj->getIgnore()) return true;

    // Object outside of playable/usuable view
    int colli_x = abs(
        Object2D::distX(player, obj) - player->camera.offset.x
    );
    int colli_y = abs(
        Object2D::distY(player, obj) - player->camera.offset.y
    );

    bool outside_window = 
        colli_x - obj->getWidth() / 2 > CFG->WIDTH ||
        colli_y - obj->getHeight() / 2 > CFG->HEIGHT;

    // Object outside of player cam border

    ObjectBox oBox = obj->getBox();
    ObjectBox bBox = player->camera.focus_border;
    ObjectBox dBox = player->camera.focus_dir;

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

int Camera::objectDrawX(Player *player, Object2D *obj)
{
    // X is fine
    int dist_x = Object2D::distX(obj, player);

    return (player->camera.unfocus.x ?
            CFG->WIDTH/2 + obj->getX() - player->camera.unfocus_offset.x - obj->getWidth()/2 :
            CFG->WIDTH/2 + dist_x + player->camera.offset.x - obj->getWidth()/2);
}
int Camera::objectDrawY(Player *player, Object2D *obj)
{
    // Y focus is fine but unfocus is a piece of shit
    int dist_y = Object2D::distY(obj, player);

    return (player->camera.unfocus.y ?
            CFG->HEIGHT/2 - obj->getY() + player->camera.unfocus_offset.y - obj->getHeight()/2 :
            CFG->HEIGHT/2 - dist_y - player->camera.offset.y - obj->getHeight()/2);
}