#ifndef BUBBLE_H
#define BUBBLE_H

#include <object2D.h>

#define Bubble1D std::vector<Bubble*>
#define BubbleObject1D std::vector<BubbleObject>

class Bubble;

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

// The reason for the existance of BubbleObject is because
struct BubbleObject
{
    SDL_Texture *texture;
    BubbleStyle style;

    SDL_Rect desRect;

    // ~BubbleObject();
    // == Update ==
    void update(Bubble *bubble, Player *player);
    void draw(Player *player);
};

class Map;
class Player;
class Multiplayer;
class Bubble : public Object2D
{
private:
    string0D bubble_path;
    BubbleObject1D bubble_objs;

public:
    short type;
    BubbleStyle style;
    ObjectBox active_box;

    ~Bubble();
    Bubble( string0D bPath, ObjectHitbox bHitbox,
            ObjectBox bActivebox, BubbleStyle bStyle,
            short type = 0, int grid = 64 );

    void update(Multiplayer *multi);
    void draw(Multiplayer *multi);

    // File Manip
    static Bubble *codeToBubbleInfo(string0D str);
    static void appendBubble(Map *map, string0D bubble_dir);
};

#endif