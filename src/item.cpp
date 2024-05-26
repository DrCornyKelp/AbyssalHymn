#include <item.h>

Item::Item(float X, float Y, short e, int w, int h, short gr, int hw, int hh, int sim, int sfm, int si, int sf)
{}

void Item::initItemSprite()
{
    const char *path;
    switch(effect)
    {
    case 1:
        path = "assets/nakuru_bake.png";
        break;
    case 2:
        path = "assets/hamster.png";
        break;
    default:
        break;
    }

    item_texture = CFG->loadTexture(path);
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
}