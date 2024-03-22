#ifndef BLOCK_H
#define BLOCK_H

#include "game.h"
#include "object2D.h"

class Player;
class Block : public Object2D
{
private:
    // Sprite handler
    std::vector<std::vector<Sprite*>> block_sprites;
    short grid;
    short grid_w, grid_h;

    bool isMoving = false;
    bool isGoThru = false;
    bool isSeeThru = false;
    bool isStepOn = false;
    short isHugged = 0;
    bool isOutBound = false;

    int seeAlpha = 255;

    float vel_x = 0, vel_y = 0;

public:
    // using::Object2D; // Allow direct usage of Object2D's contructor
    Block(float X = 0, float Y = 0, float w = 1, float h = 1, short gr = 64, bool gothru = false, bool seethru = false);

    void blockEngine(SDL_Renderer *renderer, std::vector<const char*> sPath, std::vector<std::vector<int>> b_index);

    void setGoThru(bool gothru);
    void setSeeThru(bool seethru);
    void setSeeAlpha(int alpha);
    void setStepOn(bool step);
    void setOutBound(bool oob);
    void setHugged(short hug);
    void setVelX(float X);
    void setVelY(float Y);

    bool getGoThru();
    bool getSeeThru();
    int getSeeAlpha();
    bool getStepOn();
    bool getOutBound();
    short getHugged();
    float getVelX();
    float getVelY();

    void draw(SDL_Renderer *renderer, Player *player);
};

#endif