#ifndef BLOCK_H
#define BLOCK_H

#include <player.h>
#include <object2D.h>
#include <collision.h>

#define Block1D std::vector<Block*>
#define Block2D std::vector<Block1D>

struct BlockGrid
{
    int lx, by, w, h;
    int2D index = {};
};

class Map;
class Block : public Object2D
{
private:
    // Sprite handler
    SDLTexture2D block_textures;
    int2D block_indexs;
    string1D block_paths;

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
    bool can_hug = false;

    // Condition
    bool isMoving = 0;
    bool isStepOn = 0;
    short isHugged = 0;

    // Movement
    float vel_x = 0, vel_y = 0;

    // Developer
    bool highlight = 0;
    SDL_Texture *highlight_texture;

public:
    bool isValid = 1;
    bool needReset = 0;

    // Destructor
    ~Block();
    // Default
    Block();
    // Read From File
    Block(float1D main_val);
    // Simple
    Block(float X, float Y, float w, float h, short type = 0, short gr = 64);
    // Simple (with predefined index)
    Block(float X, float Y, short t, int2D b_index);
    void blockEngine(string1D sPath, int2D bIndex = {});

    void setType(short t);
    void setSeeAlpha(int alpha);
    void setStepOn(bool step);
    void setHugged(short hug);

    short getType();
    bool isType(short t);
    int getSeeAlpha();
    bool getStepOn();
    short getHugged();

    BlockGrid getGrid();

    bool getCanHug();

    bool getHighlight();
    // 0: off, 1: on, everthing else: toggle on/off
    //                            (like a light switch)
    void setHighlight(short hl = 2);

    SDLTexture2D getBlockTextures();
    int2D getBlockIndexs();

    void blockSeethrough(Map *map, bool yes = 0);
    void blockCollision(Map *map, Player *player, PlayerState &pState);
    void draw(Player *player);

    // ============================ BLOCK MANIPULATION =============================

    void setBlockIndexs(int2D newIndex);
    void refreshTexture(string1D sPath = {});
    void tileEdit(string1D sPath, int1D tIndex, int bIndex);
    void overlap(int2D overlap, int offX, int offY);
};

#endif