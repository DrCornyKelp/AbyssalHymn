#include <item.h>

Item::Item(float X, float Y, short e, int w, int h, short gr, int hw, int hh, int sim, int sfm, int si, int sf) : 
    Object2D((X + w/2) * gr, (Y + h/2) * gr,
            w * gr, h * gr, w * gr, h * gr,
            w, h, sim, sfm, si, sf), effect(e)
{}

void Item::initItemSprite()
{
    const char *path;
    switch(effect)
    {
    case 1:
        path = "res/nakuru_bake.png";
        break;
    case 2:
        path = "res/hamster.png";
        break;
    default:
        break;
    }

    item_texture = loadTexture(path);
}

// void Item::initEffect()
// {
//     for (int i = 0; i < 5; i++)
//     {
//         effect.push_back(false);
//     }
// }

// void Item::setEffect(bool e, int i)
// {
//     effect[i] = e;
// }

short Item::getEffect()
{
    return effect;
}

void Item::draw(Player *player)
{
//     if (vel_x != 0 || vel_y != 0)
//     {
//         is_moving = true;
//         setX(getX() + vel_x);
//         setY(getY() + vel_y);
//     }
//     else
//         is_moving = false;

//     if (is_out_of_bound) return;

    // Draw
    int colli_x = abs(player->getX() - getX()) - ((player->getWidth() + getWidth()) / 2);
    int colli_y = abs(player->getY() - getY()) - ((player->getHeight() + getHeight()) / 2);

    SDL_Rect desRect = {Camera::objectDrawX(player, this),
                        Camera::objectDrawY(player, this),
                        getWidth(), getHeight()};

    SDL_RenderCopy(CFG->RENDERER, item_texture, NULL, &desRect);
}