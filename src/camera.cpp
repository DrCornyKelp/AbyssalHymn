#include <multiplayer.h>

bool Camera::outOfBound(SDL_Rect desRect)
{
    return
        desRect.x + desRect.w < 0 ||
        desRect.x - desRect.w > CFG->WIDTH ||
        desRect.y + desRect.h < 0 ||
        desRect.y - desRect.h > CFG->HEIGHT;
}

bool Camera::outOfCam(Player *player, Object2D *obj)
{
    // Object outside of player cam border

    ObjectBox oBox = obj->getBox();
    ObjectBox bBox = player->camera.focus_border;
    ObjectBox dBox = player->camera.focus_dir;

    bool outside_cam = 
        // Object Must "NOT" Depend On Map Cam
        obj->cam_depend &&
        // Player Can "NOT" Render Outside Of Map Cam
        !player->camera.outside_render &&
        // For Specific use Case
    (
        // Box "NOT" Inside Cam
        (oBox.up > bBox.up && dBox.up) ||
        (oBox.down < bBox.down && dBox.down) ||
        (oBox.right > bBox.right && dBox.right) ||
        (oBox.left < bBox.left && dBox.left)
    );

    return outside_cam;
}

int Camera::objectDrawX(Player *player, Object2D *obj)
{
    // X is fine
    int dist_x = Object2D::distX(obj, player);

    return (player->camera.unfocus.x ?
            CFG->WIDTH/2 + obj->hitbox.x - player->camera.unfocus_offset.x - obj->hitbox.w/2 :
            CFG->WIDTH/2 + dist_x + player->camera.offset.x - obj->hitbox.w/2);
}
int Camera::objectDrawY(Player *player, Object2D *obj)
{
    // Y focus is fine but unfocus is a piece of shit
    int dist_y = Object2D::distY(obj, player);

    return (player->camera.unfocus.y ?
            CFG->HEIGHT/2 - obj->hitbox.y + player->camera.unfocus_offset.y - obj->hitbox.h/2 :
            CFG->HEIGHT/2 - dist_y - player->camera.offset.y - obj->hitbox.h/2);
}