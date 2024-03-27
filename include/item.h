#ifndef ITEM_H
#define ITEM_H

#include "object2D.h"
#include "player.h"

class Player;
class Item : public Object2D
{
private:
    Sprite *item_sprite;
    short effect; // 0: no effect
                // 1: jellyfish (bullet)
                // 2: higher jumps
                // 3: speed boost
                // 4: damage boost
                // 5: invincibility

    short grid;
    float vel_x = 0, vel_y = 0;
    bool is_moving = false;
    bool is_out_of_bound = false;

public:
    Item(float X = 0, float Y = 0, short e = 0, int w = 1, int h = 1, short gr = 64, int hw = 0, int hh = 0, int sim = 0, int sfm = 0, int si = 0, int sf = 0);

    void initItemSprite(SDL_Renderer *renderer);
    // void setEffect(bool e, int i);
    short getEffect();
    void draw(SDL_Renderer *renderer, Player *player);
};

#endif