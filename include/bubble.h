#ifndef BUBBLE_H
#define BUBBLE_H

#include <object2D.h>

#define Bubble1D std::vector<Bubble*>

struct BubbleStyle
{
    // Max Value (for initialization)
    int maxOffX = 0,
        maxOffY = 0;
    float maxAlpha = 200;
    // Current Value (for runtime)
    int curOffX = 0,
        curOffY = 0;
    float curAlpha = 0;

    float alphaRatio();
};

class Map;
class Player;
class Bubble : public Object2D
{
private:
    std::string bubble_path;
    SDL_Texture *bubble_texture;

    short b_type;
    ObjectBox b_active_box;
    BubbleStyle b_style;

public:
    ~Bubble();
    Bubble( std::string bPath, ObjectHitbox bHitbox,
            ObjectBox bActivebox, BubbleStyle bStyle,
            short type = 0, int grid = 64 );
    // == Init ==
    void initBubble();
    // == Update ==
    void updateBubble(Map *map);
    // == Draw ==
    void draw(Player *player);

    // File Manip
    static Bubble *codeToBubbleInfo(std::string str);
    static void appendBubble(Map *map, std::string bubble_dir);
};

#endif