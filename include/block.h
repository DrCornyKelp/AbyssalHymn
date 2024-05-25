#ifndef BLOCK_H
#define BLOCK_H

#include <player.h>
#include <collision.h>

#define Block1D std::vector<Block*>
#define Block2D std::vector<Block1D>

struct BlockGrid
{
    int lx, by, w, h;
    int2D index = {};
};

struct BlockRect
{
    SDL_Texture *texture;
    SDL_Rect *rect;
    int index;
    string0D path;
};

struct BlockState
{
    // Condition
    bool moving = 0;
    bool stepOn = 0;
    short hugged = 0; // -1: left, 1: right
};

class Map;
class Block : public Object2D
{
public:
    // Sprite handler
    SDLTexture2D textures;
    SDLRect2D rects;
    bool2D noRenders;
    int2D indexs;
    string1D paths;

    // Default
    short grid = 64;
    int seeAlpha = 255;

    // 0:Solid
    // 1:Ice
    // 2:GoThrough
    // 3:Bridge
    // 4:Water
    // 5:SeeThrough
    // 6:TEXTURE
    short type = 0;

    // State
    BlockState state;

    // Condition
    bool can_hug = false;

    // Movement
    float vel_x = 0, vel_y = 0;

    // Developer
    bool highlight = 0;
    SDL_Texture *highlight_texture;
    bool isValid = 1;
    bool needReset = 0;

    ~Block();
    Block();
    // Read From File
    Block(float1D main_val);
    // Simple
    Block(float X, float Y, float w, float h, short type = 0, short gr = 64);
    // Simple (with predefined index)
    Block(float X, float Y, short t, int2D b_index);
    // Block Engine
    void blockEngine(string1D sPath, int2D bIndex = {});

    BlockGrid getGrid();

    void setHighlight(short hl = 2);
    void setBlockIndexs(int2D newIndex);

    void blockSeethrough(Player *player, bool yes = 0);
    void blockCollision(Map *map, Player *player, PlayerState &pState);
    void drawProp(Player *player);
    void draw(Player *player);

    // ============================ BLOCK MANIPULATION =============================

    void refreshTexture(string1D sPath = {});
    void tileEdit(string1D sPath, int1D tIndex, int bIndex);
    void overlap(int2D overlap, int offX, int offY);
};

#endif