#include <camera.h>
#include <object2D.h>
#include <player.h>

// Note!!!: objectDistance is a vector in both direction,
// not the absolute value
DistXY Camera::objectDistance(Object2D *objMain, Object2D *objSub)
{
    int distX = objMain->getX() - objSub->getX();
    int distY = objMain->getY() - objSub->getY();

    return std::make_tuple(int(distX), int(distY));
}

bool Camera::objectOutBound(Player *player, Object2D *obj)
{
    auto distance = objectDistance(player, obj);
    int colli_x = abs(DistGet(distance, 0));
    int colli_y = abs(DistGet(distance, 1));

    return  colli_x - obj->getWidth() / 2 > Game::WIDTH / player->getCameraScale() ||
            colli_y - obj->getHeight() / 2 > Game::HEIGHT / player->getCameraScale();
}

void Camera::objectSetSprite(Object2D *obj, bool end_lock)
{
    // Frame index shitty bang bang stuff handler
    if (obj->getSprIndexMax())
    {
        if (obj->getSprFrame() < obj->getSprFrameMax())
        {
            obj->setSprFrame(obj->getSprFrame() + 1);
        }
        else
        {
            obj->setSprFrame(0);
            obj->setSprIndex(obj->getSprIndex() + 1);
        }

        if (obj->getSprIndex() >= obj->getSprIndexMax())
            if (end_lock)
            obj->setSprIndex(obj->getSprIndexMax() - 1);
        else
            obj->setSprIndex(0);
    }
}

int Camera::playerShiftX(Player *player)
{
    return    player->getEaseX()
            + player->getEffectX();
}
int Camera::playerShiftY(Player *player)
{
    return    player->getEaseY()
            + player->getVerticalAhead(); // Gameplay advantage move
            + player->getEffectY();
}

int Camera::objectDrawX(Player *player, Object2D *obj)
{
    // X is fine
    auto distance = Camera::objectDistance(obj, player);
    int dist_x = DistGet(distance, 0);

    return (player->getUnfocusX() ?
            Game::WIDTH/2 + (obj->getX() - player->getUnfocusOffsetX() - obj->getWidth()/2) * player->getCameraScale() :
            Game::WIDTH/2 + (dist_x + player->getOffsetMidX() - obj->getWidth()/2) * player->getCameraScale())
            + Camera::playerShiftX(player);
}
int Camera::objectDrawY(Player *player, Object2D *obj)
{
    // Y focus is fine but unfocus is a piece of shit
    auto distance = Camera::objectDistance(obj, player);
    int dist_y = DistGet(distance, 1);

    return (player->getUnfocusY() ?
            Game::HEIGHT/2 - (obj->getY() - player->getUnfocusOffsetY() + obj->getHeight()/2) * player->getCameraScale() :
            Game::HEIGHT/2 - (dist_y + player->getOffsetMidY() + obj->getHeight()/2) * player->getCameraScale())
            + Camera::playerShiftY(player);
}